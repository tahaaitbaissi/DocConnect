#include "AdminController.h"

AdminController::AdminController() {}
AdminController::~AdminController() {}

// Get all users (patients and doctors)
vector<User> AdminController::getAllUsers(OracleConnection& conn) {
    vector<User> users;
    string query = "SELECT user_id FROM Users";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        User user;
        int userId = stoi(row.at("USER_ID"));
        if (user.read(conn, userId)) {
            users.push_back(user);
        }
    }
    return users;
}

vector<Ville> AdminController::getAllCities(OracleConnection& conn) {
    vector<Ville> villes;
    string query = "SELECT ville_id FROM villes";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Ville ville;
        int villeId = stoi(row.at("VILLE_ID"));
        if (ville.read(conn, villeId)) {
            villes.push_back(ville);
        }
    }
    return villes;
}

vector<Categorie> AdminController::getAllCategories(OracleConnection& conn) {
    vector<Categorie> cats;
    string query = "SELECT categorie_id FROM categories";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Categorie cat;
        int catId = stoi(row.at("CATEGORIE_ID"));
        if (cat.read(conn, catId)) {
            cats.push_back(cat);
        }
    }
    return cats;
}

vector<Soins> AdminController::getAllSoins(OracleConnection& conn, int categorieId) {
    vector<Soins> soins;
    string query = "SELECT soin_id FROM Soins WHERE categorie_id = " + to_string(categorieId);
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Soins soin;
        int soinId = stoi(row.at("SOIN_ID"));
        if (soin.read(conn, soinId)) {
            soins.push_back(soin);
        }
    }
    return soins;
}

// Delete a user by userId
void AdminController::deleteUser(OracleConnection& conn, int userId) {
    string query = "DELETE FROM Users WHERE user_id = " + to_string(userId);
    conn.executeQuery(query);
}

// Get all doctors
vector<Doctor> AdminController::getAllDoctors(OracleConnection& conn) {
    vector<Doctor> doctors;
    string query = "SELECT user_id FROM Users WHERE role = 'doctor'";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Doctor doctor;
        int doctorId = stoi(row.at("USER_ID"));
        if (doctor.read(conn, doctorId)) {
            doctors.push_back(doctor);
        }
    }
    return doctors;
}

// Get all patients
vector<Patient> AdminController::getAllPatients(OracleConnection& conn) {
    vector<Patient> patients;
    string query = "SELECT user_id FROM Users WHERE role = 'patient'";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Patient patient;
        int patientId = stoi(row.at("USER_ID"));
        if (patient.read(conn, patientId)) {
            patients.push_back(patient);
        }
    }
    return patients;
}

// Update doctor details
void AdminController::updateDoctorDetails(OracleConnection& conn, int doctorId, string workHours, string description) {
    string query = "UPDATE Users SET heure_travail = '" + workHours + "', description = '" + description + "' WHERE user_id = " + to_string(doctorId);
    conn.executeQuery(query);
}

// Update patient details
void AdminController::updatePatientDetails(OracleConnection& conn, int patientId, string dateOfBirth) {
    string query = "UPDATE Users SET date_naissance = '" + dateOfBirth + "' WHERE user_id = " + to_string(patientId);
    conn.executeQuery(query);
}



