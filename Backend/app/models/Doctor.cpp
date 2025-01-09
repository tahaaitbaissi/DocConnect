#include "Doctor.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Doctor::Doctor() : User(), workHours(""), description(""), consultationType(""), categorieId(0), villeId(0) {}

Doctor::Doctor(int userId, string nom, string prenom, string email,
               string password, string adresse, string telephone, string sexe,
               string workHours, string description, string consultationType,
               int categorieId, int villeId)
: User(userId, nom, prenom, email, password, adresse, telephone, sexe),
workHours(workHours), description(description), consultationType(consultationType), categorieId(categorieId), villeId(villeId) {}

Doctor::~Doctor() {}

void Doctor::create(OracleConnection& conn) {
    // Create user first
    User::create(conn);

    // Insert doctor-specific data into Users table (workHours, description, consultationType, categorieId, villeId)
    string query = "UPDATE Users SET heure_travail = '" + workHours + "', description = '" + description +
    "', type_consultation = '" + consultationType + "', categorie_id = " + to_string(categorieId) +
    ", ville_id = " + to_string(villeId) +", role = 'doctor'" +" WHERE user_id = " + to_string(getId());
    conn.executeQuery(query);
}

bool Doctor::read(OracleConnection& conn, int userId) {
    // Read user-specific data from Users table (doctor data is included within Users)
    bool result = User::read(conn, userId);

    if (result) {
        // Read doctor-specific data
        string query = "SELECT heure_travail, description, type_consultation, categorie_id, ville_id FROM Users WHERE user_id = " + to_string(userId);
        vector<map<string, string>> resultData = conn.executeQuery(query);

        if (!resultData.empty()) {
            map<string, string> row = resultData[0];
            workHours = row["HEURE_TRAVAIL"];
            description = row["DESCRIPTION"];
            consultationType = row["TYPE_CONSULTATION"];
            categorieId = stoi(row["CATEGORIE_ID"]);
            villeId = stoi(row["VILLE_ID"]);
        }
    }

    return result;
}

void Doctor::update(OracleConnection& conn) {
    // Update user data first
    User::update(conn);

    // Then update doctor-specific data within Users table
    string query = "UPDATE Users SET heure_travail = '" + workHours + "', description = '" + description +
    "', type_consultation = '" + consultationType + "', categorie_id = " + to_string(categorieId) +
    ", ville_id = " + to_string(villeId) + " WHERE user_id = " + to_string(getId());
    conn.executeQuery(query);
}

void Doctor::deleteRecord(OracleConnection& conn) {
    // Delete doctor-specific data (handled by deleting the entire user)
    User::deleteRecord(conn);
}

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

void Doctor::setSoins(vector<int> soins) {
    this->soins = soins;
}

void Doctor::addSoin(OracleConnection& conn, int soinId) {
    string query = "INSERT INTO Doctor_Soins (doctor_id, soin_id) VALUES (" + to_string(getId()) + ", " + to_string(soinId) + ")";
    conn.executeQuery(query);
}

void Doctor::removeSoin(OracleConnection& conn, int soinId) {
    string query = "DELETE FROM Doctor_Soins WHERE doctor_id = " + to_string(getId()) + " AND soin_id = " + to_string(soinId);
    conn.executeQuery(query);
}

void Doctor::loadSoins(OracleConnection& conn) {
    string query = "SELECT soin_id FROM Doctor_Soins WHERE doctor_id = " + to_string(getId());
    vector<map<string, string>> resultData = conn.executeQuery(query);

    soins.clear();  // Clear the current soins list

    for (const auto& row : resultData) {
        soins.push_back(stoi(row.at("SOIN_ID")));
    }
}



