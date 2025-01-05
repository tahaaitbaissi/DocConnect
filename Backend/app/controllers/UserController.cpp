#include "UserController.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

UserController::UserController() {}
UserController::~UserController() {}

void UserController::addUser(OracleConnection& conn, User& user) {
    user.create(conn);
    cout << "User added successfully." << endl;
}

bool UserController::getUser(OracleConnection& conn, int id, User& user) {
    if (user.read(conn, id)) {
        cout << "User retrieved successfully." << endl;
        return true;
    } else {
        cout << "User not found with ID: " << id << endl;
        return false;
    }
}

vector<User> UserController::getAllUsers(OracleConnection& conn) {
    vector<User> users;
    string query = "SELECT user_id FROM Users";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        User user;
        int id = stoi(row.at("USER_ID"));
        if (user.read(conn, id)) {
            users.push_back(user);
        }
    }
    return users;
}

bool UserController::updateUser(OracleConnection& conn, User& user) {
    try {
        user.update(conn);
        cout << "User updated successfully." << endl;
        return true;
    } catch (...) {
        cout << "Failed to update user with ID: " << user.getId() << endl;
        return false;
    }
}

bool UserController::deleteUser(OracleConnection& conn, int id) {
    User user;
    if (user.read(conn, id)) {
        user.deleteRecord(conn);
        cout << "User deleted successfully." << endl;
        return true;
    } else {
        cout << "Failed to delete user. User not found with ID: " << id << endl;
        return false;
    }
}

User UserController::login(OracleConnection& conn, string email, string password) {
    string query = "SELECT user_id FROM Users WHERE email = '" + email + "' AND password = '" + password + "'";
    vector<map<string, string>> result = conn.executeQuery(query);

    User user;

    if (!result.empty()) {
        cout << "Login successful for user ID: " << result[0]["USER_ID"] << endl;
        user.read(conn, stoi(result[0]["USER_ID"]));
        return user;
    } else {
        cout << "Invalid email or password." << endl;
        return user;
    }
}

bool UserController::registerUser(OracleConnection& conn, User* user) {
    string query = "SELECT COUNT(*) AS count FROM Users WHERE email = '" + user->getEmail() + "'";
    vector<map<string, string>> result = conn.executeQuery(query);

    if (!result.empty() && stoi(result[0]["COUNT"]) > 0) {
        cout << "Email already registered: " << user->getEmail() << endl;
        return false;
    } else {
        user->create(conn);
        cout << "Registration successful for email: " << user->getEmail() << endl;
        return true;
    }
}
