#include "PatientController.h"
#include <iostream>

PatientController::PatientController() {}
PatientController::~PatientController() {}

// Fetch all appointments for a given patient
vector<RendezVous> PatientController::getAppointmentsForPatient(OracleConnection& conn, int patientId) {
    vector<RendezVous> appointments;
    string query = "SELECT rendezvous_id FROM RendezVous WHERE patient_id = " + to_string(patientId);
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        RendezVous appointment;
        int id = stoi(row.at("RENDEZVOUS_ID"));
        if (appointment.read(conn, id)) {
            appointments.push_back(appointment);
        }
    }
    return appointments;
}

// Schedule a new appointment for a patient
bool PatientController::scheduleAppointment(OracleConnection& conn, int patientId, RendezVous& appointment) {
    try {
        appointment.create(conn);
        cout << "Appointment scheduled for patient ID: " << patientId << endl;
        return true;
    } catch (...) {
        cout << "Failed to schedule appointment for patient ID: " << patientId << endl;
        return false;
    }
}

// Search for patients by name
vector<Patient> PatientController::searchPatientsByName(OracleConnection& conn, string name) {
    vector<Patient> patients;
    string query = "SELECT user_id FROM User WHERE LOWER(nom) LIKE '%" + name + "%'";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Patient patient;
        int id = stoi(row.at("PATIENT_ID"));
        if (patient.read(conn, id)) {
            patients.push_back(patient);
        }
    }
    return patients;
}

// Count the number of appointments for a patient
int PatientController::countAppointmentsForPatient(OracleConnection& conn, int patientId) {
    string query = "SELECT COUNT(*) AS appointment_count FROM RendezVous WHERE patient_id = " + to_string(patientId);
    vector<map<string, string>> result = conn.executeQuery(query);

    if (!result.empty()) {
        return stoi(result[0].at("APPOINTMENT_COUNT"));
    }
    return 0;
}
