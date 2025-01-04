#include "admin_routes.h"

void setupAdminRoutes(crow::SimpleApp& app, OracleConnection& conn) {
    AdminController adminController;

    // 1. Get all users
    CROW_ROUTE(app, "/admin/users")
    ([&conn, &adminController]() {
        auto users = adminController.getAllUsers(conn);
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

    // 2. Delete a user by ID
    CROW_ROUTE(app, "/admin/users/<int>").methods(crow::HTTPMethod::DELETE)
    ([&conn, &adminController](int userId) {
        try {
            adminController.deleteUser(conn, userId);
            return crow::response(200, "User deleted successfully.");
        } catch (const std::exception& e) {
            return crow::response(400, std::string("Error: ") + e.what());
        }
    });

    // 3. Get all doctors
    CROW_ROUTE(app, "/admin/doctors")
    ([&conn, &adminController]() {
        auto doctors = adminController.getAllDoctors(conn);
        crow::json::wvalue response;

        for (size_t i = 0; i < doctors.size(); ++i) {
            response[i]["id"] = doctors[i].getId();
            response[i]["nom"] = doctors[i].getNom();
            response[i]["prenom"] = doctors[i].getPrenom();
            response[i]["email"] = doctors[i].getEmail();
            response[i]["adresse"] = doctors[i].getAdresse();
            response[i]["telephone"] = doctors[i].getTelephone();
            response[i]["sexe"] = doctors[i].getSexe();
            response[i]["work_hours"] = doctors[i].getWorkHours();
            response[i]["description"] = doctors[i].getDescription();
            response[i]["consultation_type"] = doctors[i].getConsultationType();
            response[i]["categorie_id"] = doctors[i].getCategorieId();
            response[i]["ville_id"] = doctors[i].getVilleId();
        }

        return response;
    });

    // 4. Get all patients
    CROW_ROUTE(app, "/admin/patients")
    ([&conn, &adminController]() {
        auto patients = adminController.getAllPatients(conn);
        crow::json::wvalue response;

        for (size_t i = 0; i < patients.size(); ++i) {
            response[i]["id"] = patients[i].getId();
            response[i]["nom"] = patients[i].getNom();
            response[i]["prenom"] = patients[i].getPrenom();
            response[i]["email"] = patients[i].getEmail();
            response[i]["adresse"] = patients[i].getAdresse();
            response[i]["telephone"] = patients[i].getTelephone();
            response[i]["sexe"] = patients[i].getSexe();
            response[i]["date_of_birth"] = patients[i].getDateOfBirth();
        }

        return response;
    });

    // 5. Update doctor details
    CROW_ROUTE(app, "/admin/doctors/<int>").methods(crow::HTTPMethod::PUT)
    ([&conn, &adminController](const crow::request& req, int doctorId) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("work_hours") || !body.has("description")) {
            return crow::response(400, "Invalid input data.");
        }

        std::string workHours = body["work_hours"].s();
        std::string description = body["description"].s();

        try {
            adminController.updateDoctorDetails(conn, doctorId, workHours, description);
            return crow::response(200, "Doctor details updated successfully.");
        } catch (const std::exception& e) {
            return crow::response(400, std::string("Error: ") + e.what());
        }
    });

    // 6. Update patient details
    CROW_ROUTE(app, "/admin/patients/<int>").methods(crow::HTTPMethod::PUT)
    ([&conn, &adminController](const crow::request& req, int patientId) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("date_of_birth")) {
            return crow::response(400, "Invalid input data.");
        }

        std::string dateOfBirth = body["date_of_birth"].s();

        try {
            adminController.updatePatientDetails(conn, patientId, dateOfBirth);
            return crow::response(200, "Patient details updated successfully.");
        } catch (const std::exception& e) {
            return crow::response(400, std::string("Error: ") + e.what());
        }
    });
}

