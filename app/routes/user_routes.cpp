#include "user_routes.h"

void setupUserRoutes(crow::SimpleApp& app, OracleConnection& conn) {
    UserController userController;

    // 1. Register a new user
    CROW_ROUTE(app, "/user/register").methods(crow::HTTPMethod::POST)
    ([&conn, &userController](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("email") || !body.has("password")) {
            return crow::response(400, "Invalid input data.");
        }

        string email = body["email"].s();
        string password = body["password"].s();
        User newUser;
        newUser.setEmail(email);
        newUser.setPassword(password);

        bool success = userController.registerUser(conn, newUser);
        if (success) {
            return crow::response(200, "Registration successful.");
        } else {
            return crow::response(400, "Email already registered.");
        }
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

        bool success = userController.login(conn, email, password);
        if (success) {
            return crow::response(200, "Login successful.");
        } else {
            return crow::response(400, "Invalid email or password.");
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
