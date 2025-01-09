#include "user_routes.h"

#include "../models/Patient.h"
#include "../models/Doctor.h"

void setupUserRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn) {
    UserController userController;
    DoctorController doctorController;

    // 1. Register a new user
    // CROW_ROUTE(app, "/user/register").methods(crow::HTTPMethod::POST)
    // ([&conn, &userController](const crow::request& req) {
    //     auto body = crow::json::load(req.body);
    //     if (!body || !body.has("email") || !body.has("password")) {
    //         return crow::response(400, "Invalid input data.");
    //     }
    //
    //     string email = body["email"].s();
    //     string password = body["password"].s();
    //     string nom = body["firstName"].s();
    //     string prenom = body["lastName"].s();
    //     string address = body["address"].s();
    //     string telephone = body["phone"].s();
    //     string sexe = body["gender"].s();
    //     string role = body["role"].s();
    //     User *newUser;
    //
    //     if (role == "patient") {
    //         newUser = new Patient();
    //     } else {
    //         newUser = new Doctor();
    //     }
    //
    //     newUser->setEmail(email);
    //     newUser->setPassword(password);
    //     newUser->setNom(nom);
    //     newUser->setPrenom(prenom);
    //     newUser->setAdresse(address);
    //     newUser->setTelephone(telephone);
    //     newUser->setSexe(sexe);
    //     newUser->setRole(role);
    //
    //     bool success = userController.registerUser(conn, newUser);
    //     if (success) {
    //         return crow::response(200, "Registration successful.");
    //     } else {
    //         return crow::response(400, "Email already registered.");
    //     }
    // });

    CROW_ROUTE(app, "/user/register").methods(crow::HTTPMethod::POST)
    ([&conn, &userController, &doctorController](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("email") || !body.has("password")) {
            return crow::response(400, crow::json::wvalue{{"error", "Invalid input data."}});
        }

        string email = body["email"].s();
        string password = body["password"].s();
        string nom = body["firstName"].s();
        string prenom = body["lastName"].s();
        string address = body["address"].s();
        string telephone = body["phone"].s();
        string sexe = body["gender"].s();
        string role = body["role"].s();

        User* newUser;

        if (role == "patient") {
            newUser = new Patient();
        } else if (role == "doctor") {
            newUser = new Doctor();
        } else {
            return crow::response(400, crow::json::wvalue{{"error", "Invalid role."}});
        }

        newUser->setEmail(email);
        newUser->setPassword(password);
        newUser->setNom(nom);
        newUser->setPrenom(prenom);
        newUser->setAdresse(address);
        newUser->setTelephone(telephone);
        newUser->setSexe(sexe);
        newUser->setRole(role);

        std::vector<int> soinsIds;

        // Handle patient-specific data
        if (role == "patient") {
            if (!body.has("birthDate")) {
                return crow::response(400, crow::json::wvalue{{"error", "Birth date is required for patients."}});
            }
            string birthDate = body["birthDate"].s();
            dynamic_cast<Patient*>(newUser)->setDateOfBirth(birthDate);
        }

        // Handle doctor-specific data
        if (role == "doctor") {
            if (!body.has("workHours") || !body.has("description") || !body.has("consultationType") ||
                !body.has("ville") || !body.has("category") || !body.has("soins")) {
                return crow::response(400, crow::json::wvalue{{"error", "Missing required fields for doctor."}});
            }

            string workHours = body["workHours"].s();
            string description = body["description"].s();
            string consultationType = body["consultationType"].s();
            int ville = body["ville"].i();
            int category = body["category"].i();
            auto soins = body["soins"];

            if (soins.t() != crow::json::type::List) {
                return crow::response(400, crow::json::wvalue{{"error", "Soins should be an array."}});
            }

            for (const auto& soin : soins) {               
                if (soin.t() == crow::json::type::Object && soin.has("id")) {
                    soinsIds.push_back(soin["id"].i());
                } else {
                    return crow::response(400, crow::json::wvalue{{"error", "Invalid soin object. Missing 'id'."}});
                }
            }

            auto* doctor = dynamic_cast<Doctor*>(newUser);
            doctor->setWorkHours(workHours);
            doctor->setDescription(description);
            doctor->setConsultationType(consultationType);
            doctor->setVilleId(ville);
            doctor->setCategorieId(category);
            doctor->setSoins(soinsIds);
        }

        bool success = userController.registerUser(conn, newUser);
        if (!success) {
            return crow::response(400, crow::json::wvalue{{"error", "Email already registered."}});
        }

        if (role == "doctor") {
            auto* doctor = dynamic_cast<Doctor*>(newUser);
            // Handle adding the soins to the doctor in the database
            if (!doctorController.addSoinsToDoctor(conn, doctor->getId(), soinsIds)) {
                return crow::response(400, crow::json::wvalue{{"error", "Failed to assign soins to the doctor."}});
            }
        }

        return crow::response(200, crow::json::wvalue{{"message", "Registration successful."}});
    });



    // 2. User login
    CROW_ROUTE(app, "/user/login").methods(crow::HTTPMethod::POST)
    ([&conn, &userController](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("email") || !body.has("password")) {
            return crow::response(400, "Invalid input data.");
        }

        string email = body["email"].s();
        string password = body["password"].s();

        User user = userController.login(conn, email, password);
        if (user.getId()) {
            crow::json::wvalue response;
            response["message"] = "Login successful.";
            response["id"] = user.getId();
            response["nom"] = user.getNom();
            response["prenom"] = user.getPrenom();
            response["email"] = user.getEmail();
            response["adresse"] = user.getAdresse();
            response["telephone"] = user.getTelephone();
            response["sexe"] = user.getSexe();
            response["role"] = user.getRole();

            return crow::response(200, response);
        } else {
            crow::json::wvalue errorResponse;
            errorResponse["error"] = "Invalid email or password.";
            return crow::response(401, errorResponse);
        }
    });

    // 3. Get user by ID
    CROW_ROUTE(app, "/user/<int>").methods(crow::HTTPMethod::GET)
    ([&conn, &userController](int userId) {
        User user;
        bool success = userController.getUser(conn, userId, user);
        if (success) {
            crow::json::wvalue response;
            response["id"] = user.getId();
            response["nom"] = user.getNom();
            response["prenom"] = user.getPrenom();
            response["email"] = user.getEmail();
            response["adresse"] = user.getAdresse();
            response["telephone"] = user.getTelephone();
            response["sexe"] = user.getSexe();
            response["role"] = user.getRole();
            return crow::response{200, response}; // return success with 200 status code
        } else {
            crow::json::wvalue error_response;
            error_response["error"] = "User not found.";
            return crow::response{404, error_response}; // return error with 404 status code
        }
    });

    // 4. Update user information
    CROW_ROUTE(app, "/user/update").methods(crow::HTTPMethod::POST)
    ([&conn, &userController](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("id") || !body.has("email") || !body.has("name")) {
            return crow::response(400, "Invalid input data.");
        }

        int userId = body["id"].i();
        string email = body["email"].s();
        string nom = body["nom"].s();
        string prenom = body["prenom"].s();
        User user;
        user.setId(userId);
        user.setEmail(email);
        user.setNom(nom);
        user.setPrenom(prenom);

        bool success = userController.updateUser(conn, user);
        if (success) {
            return crow::response(200, "User updated successfully.");
        } else {
            return crow::response(400, "Failed to update user.");
        }
    });

    // 5. Delete user by ID
    CROW_ROUTE(app, "/user/delete/<int>").methods(crow::HTTPMethod::POST)
    ([&conn, &userController](int userId) {
        bool success = userController.deleteUser(conn, userId);
        if (success) {
            return crow::response(200, "User deleted successfully.");
        } else {
            return crow::response(400, "Failed to delete user.");
        }
    });

    // 6. Get all users
    CROW_ROUTE(app, "/users").methods(crow::HTTPMethod::GET)
    ([&conn, &userController]() {
        auto users = userController.getAllUsers(conn);
        crow::json::wvalue response;

        for (size_t i = 0; i < users.size(); ++i) {
            response[i]["id"] = users[i].getId();
            response[i]["nom"] = users[i].getNom();
            response[i]["prenom"] = users[i].getPrenom();
            response[i]["email"] = users[i].getEmail();
            response[i]["adresse"] = users[i].getAdresse();
            response[i]["telephone"] = users[i].getTelephone();
            response[i]["sexe"] = users[i].getSexe();
            response[i]["role"] = users[i].getRole();
        }

        return response;
    });
}
