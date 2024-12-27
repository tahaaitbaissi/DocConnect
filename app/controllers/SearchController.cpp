#include "SearchController.h"

SearchController::SearchController() {}
SearchController::~SearchController() {}

// Search doctors by name
vector<Doctor> SearchController::searchDoctorsByName(OracleConnection& conn, string name) {
    vector<Doctor> doctors;
    string query = "SELECT doctor_id FROM Doctors WHERE nom LIKE '%" + name + "%' OR prenom LIKE '%" + name + "%'";
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

// Search patients by name
vector<Patient> SearchController::searchPatientsByName(OracleConnection& conn, string name) {
    vector<Patient> patients;
    string query = "SELECT patient_id FROM Patients WHERE nom LIKE '%" + name + "%' OR prenom LIKE '%" + name + "%'";
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

// Search appointments by doctor
vector<Rendezvous> SearchController::searchAppointmentsByDoctor(OracleConnection& conn, int doctorId) {
    vector<Rendezvous> appointments;
    string query = "SELECT rendezvous_id FROM Rendezvous WHERE doctor_id = " + to_string(doctorId);
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Rendezvous appointment;
        int appointmentId = stoi(row.at("RENDEZVOUS_ID"));
        if (appointment.read(conn, appointmentId)) {
            appointments.push_back(appointment);
        }
    }
    return appointments;
}

// Search appointments by patient
vector<Rendezvous> SearchController::searchAppointmentsByPatient(OracleConnection& conn, int patientId) {
    vector<Rendezvous> appointments;
    string query = "SELECT rendezvous_id FROM Rendezvous WHERE patient_id = " + to_string(patientId);
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Rendezvous appointment;
        int appointmentId = stoi(row.at("RENDEZVOUS_ID"));
        if (appointment.read(conn, appointmentId)) {
            appointments.push_back(appointment);
        }
    }
    return appointments;
}

// Search doctors by category
vector<Doctor> SearchController::searchDoctorsByCategory(OracleConnection& conn, int categoryId) {
    vector<Doctor> doctors;
    string query = "SELECT doctor_id FROM Doctors WHERE categorie_id = " + to_string(categoryId);
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

// Search doctors by city
vector<Doctor> SearchController::searchDoctorsByCity(OracleConnection& conn, int cityId) {
    vector<Doctor> doctors;
    string query = "SELECT doctor_id FROM Doctors WHERE ville_id = " + to_string(cityId);
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
