#include "Patient.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Patient::Patient() : User(), patientId(0), dateOfBirth("") {}

Patient::Patient(int userId, int patientId, string nom, string prenom, string email,
                 string password, string adresse, string telephone, string sexe,
                 string dateOfBirth)
: User(userId, nom, prenom, email, password, adresse, telephone, sexe),
patientId(patientId), dateOfBirth(dateOfBirth) {}

Patient::~Patient() {}

void Patient::create(OracleConnection& conn) {
    // Create user first
    User::create(conn);

    // Then insert into Patients
    string query = "INSERT INTO Patients (patient_id, user_id, date_naissance) VALUES ('" +
    to_string(patientId) + "', '" + to_string(getId()) + "', '" + dateOfBirth + "')";
    conn.executeQuery(query);
}

bool Patient::read(OracleConnection& conn, int patientId) {
    // Read patient-specific data
    string query = "SELECT * FROM Patients WHERE patient_id = " + to_string(patientId);
    vector<map<string, string>> result = conn.executeQuery(query);

    if (!result.empty()) {
        map<string, string> row = result[0];
        this->patientId = patientId;
        this->dateOfBirth = row["DATE_NAISSANCE"];

        // Read user data
        int userId = stoi(row["USER_ID"]);
        return User::read(conn, userId);
    }
    return false;
}

void Patient::update(OracleConnection& conn) {
    // Update user first
    User::update(conn);

    // Then update Patients
    string query = "UPDATE Patients SET date_naissance = '" + dateOfBirth +
    "' WHERE patient_id = " + to_string(patientId);
    conn.executeQuery(query);
}

void Patient::deleteRecord(OracleConnection& conn) {
    // Delete from Patients first
    string query = "DELETE FROM Patients WHERE patient_id = " + to_string(patientId);
    conn.executeQuery(query);

    // Then delete from Users
    User::deleteRecord(conn);
}

int Patient::getPatientId() { return patientId; }
void Patient::setPatientId(int patientId) { this->patientId = patientId; }
string Patient::getDateOfBirth() { return dateOfBirth; }
void Patient::setDateOfBirth(string dateOfBirth) { this->dateOfBirth = dateOfBirth; }
