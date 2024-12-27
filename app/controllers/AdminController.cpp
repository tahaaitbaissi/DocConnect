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

// Delete a user by userId
void AdminController::deleteUser(OracleConnection& conn, int userId) {
    string query = "DELETE FROM Users WHERE user_id = " + to_string(userId);
    conn.executeQuery(query);
}

// Get all doctors
vector<Doctor> AdminController::getAllDoctors(OracleConnection& conn) {
    vector<Doctor> doctors;
    string query = "SELECT doctor_id FROM Doctors";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Doctor doctor;
        int doctorId = stoi(row.at("DOCTOR_ID"));
        if (doctor.read(conn, doctorId)) {
            doctors.push_back(doctor);
        }
    }
    return doctors;
}

// Delete a doctor by doctorId
void AdminController::deleteDoctor(OracleConnection& conn, int doctorId) {
    string query = "DELETE FROM Doctors WHERE doctor_id = " + to_string(doctorId);
    conn.executeQuery(query);
}

// Get all patients
vector<Patient> AdminController::getAllPatients(OracleConnection& conn) {
    vector<Patient> patients;
    string query = "SELECT patient_id FROM Patients";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Patient patient;
        int patientId = stoi(row.at("PATIENT_ID"));
        if (patient.read(conn, patientId)) {
            patients.push_back(patient);
        }
    }
    return patients;
}

// Delete a patient by patientId
void AdminController::deletePatient(OracleConnection& conn, int patientId) {
    string query = "DELETE FROM Patients WHERE patient_id = " + to_string(patientId);
    conn.executeQuery(query);
}

// Update doctor details
void AdminController::updateDoctorDetails(OracleConnection& conn, int doctorId, string workHours, string description) {
    string query = "UPDATE Doctors SET heure_travail = '" + workHours + "', description = '" + description + "' WHERE doctor_id = " + to_string(doctorId);
    conn.executeQuery(query);
}

// Update patient details
void AdminController::updatePatientDetails(OracleConnection& conn, int patientId, string dateOfBirth) {
    string query = "UPDATE Patients SET date_naissance = '" + dateOfBirth + "' WHERE patient_id = " + to_string(patientId);
    conn.executeQuery(query);
}
