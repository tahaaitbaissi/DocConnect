#include "Patient.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Patient::Patient() : User(), dateOfBirth("") {}

Patient::Patient(int userId, string nom, string prenom, string email,
                 string password, string adresse, string telephone, string sexe,
                 string dateOfBirth)
: User(userId, nom, prenom, email, password, adresse, telephone, sexe),
dateOfBirth(dateOfBirth) {}

Patient::~Patient() {}

void Patient::create(OracleConnection& conn) {
    // Create user first
    User::create(conn);

    // Set the role as 'patient' for this user
    string query = "UPDATE Users SET role = 'patient', date_naissance = TO_DATE('" + dateOfBirth +
    "','YYYY-MM-DD') WHERE user_id = " + to_string(getId());
    conn.executeQuery(query);
}

bool Patient::read(OracleConnection& conn, int userId) {
    // Read user-specific data first
    bool result = User::read(conn, userId);

    if (result) {
        // Read patient-specific data from Users table
        string query = "SELECT date_naissance FROM Users WHERE user_id = " + to_string(userId);
        vector<map<string, string>> resultData = conn.executeQuery(query);

        if (!resultData.empty()) {
            map<string, string> row = resultData[0];
            dateOfBirth = row["DATE_NAISSANCE"];
        }
    }

    return result;
}

void Patient::update(OracleConnection& conn) {
    // Update user data first
    User::update(conn);

    // Then update patient-specific data in Users table
    string query = "UPDATE Users SET date_naissance = '" + dateOfBirth +
    "' WHERE user_id = " + to_string(getId());
    conn.executeQuery(query);
}

void Patient::deleteRecord(OracleConnection& conn) {
    // Delete user (which also deletes patient-specific data)
    User::deleteRecord(conn);
}

string Patient::getDateOfBirth() { return dateOfBirth; }
void Patient::setDateOfBirth(string dateOfBirth) { this->dateOfBirth = dateOfBirth; }
