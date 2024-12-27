#include "Doctor.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Doctor::Doctor() : User(), doctorId(0), workHours(""), description(""), consultationType(""), categorieId(0), villeId(0) {}

Doctor::Doctor(int userId, int doctorId, string nom, string prenom, string email,
               string password, string adresse, string telephone, string sexe,
               string workHours, string description, string consultationType,
               int categorieId, int villeId)
: User(userId, nom, prenom, email, password, adresse, telephone, sexe),
doctorId(doctorId), workHours(workHours), description(description),
consultationType(consultationType), categorieId(categorieId), villeId(villeId) {}

Doctor::~Doctor() {}

void Doctor::create(OracleConnection& conn) {
    // Create user first
    User::create(conn);

    // Insert into Doctors table
    string query = "INSERT INTO Doctors (doctor_id, user_id, heure_travail, description, type_consultation, categorie_id, ville_id) "
    "VALUES (" + to_string(doctorId) + ", " + to_string(getId()) + ", '" + workHours + "', '" + description +
    "', '" + consultationType + "', " + to_string(categorieId) + ", " + to_string(villeId) + ")";
    conn.executeQuery(query);
}

bool Doctor::read(OracleConnection& conn, int doctorId) {
    // Read doctor-specific data
    string query = "SELECT * FROM Doctors WHERE doctor_id = " + to_string(doctorId);
    vector<map<string, string>> result = conn.executeQuery(query);

    if (!result.empty()) {
        map<string, string> row = result[0];
        this->doctorId = doctorId;
        this->workHours = row["HEURE_TRAVAIL"];
        this->description = row["DESCRIPTION"];
        this->consultationType = row["TYPE_CONSULTATION"];
        this->categorieId = stoi(row["CATEGORIE_ID"]);
        this->villeId = stoi(row["VILLE_ID"]);

        // Read user data
        int userId = stoi(row["USER_ID"]);
        return User::read(conn, userId);
    }
    return false;
}

void Doctor::update(OracleConnection& conn) {
    // Update user first
    User::update(conn);

    // Update Doctors table
    string query = "UPDATE Doctors SET heure_travail = '" + workHours + "', description = '" + description +
    "', type_consultation = '" + consultationType + "', categorie_id = " + to_string(categorieId) +
    ", ville_id = " + to_string(villeId) + " WHERE doctor_id = " + to_string(doctorId);
    conn.executeQuery(query);
}

void Doctor::deleteRecord(OracleConnection& conn) {
    // Delete from Doctors first
    string query = "DELETE FROM Doctors WHERE doctor_id = " + to_string(doctorId);
    conn.executeQuery(query);

    // Then delete from Users
    User::deleteRecord(conn);
}

int Doctor::getDoctorId() { return doctorId; }
void Doctor::setDoctorId(int doctorId) { this->doctorId = doctorId; }
string Doctor::getWorkHours() { return workHours; }
void Doctor::setWorkHours(string workHours) { this->workHours = workHours; }
string Doctor::getDescription() { return description; }
void Doctor::setDescription(string description) { this->description = description; }
string Doctor::getConsultationType() { return consultationType; }
void Doctor::setConsultationType(string consultationType) { this->consultationType = consultationType; }
int Doctor::getCategorieId() { return categorieId; }
void Doctor::setCategorieId(int categorieId) { this->categorieId = categorieId; }
int Doctor::getVilleId() { return villeId; }
void Doctor::setVilleId(int villeId) { this->villeId = villeId; }
