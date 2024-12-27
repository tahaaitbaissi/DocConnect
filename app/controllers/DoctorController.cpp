#include "DoctorController.h"
#include <iostream>

DoctorController::DoctorController() {}
DoctorController::~DoctorController() {}

// Get all appointments for a specific doctor
vector<RendezVous> DoctorController::getAppointmentsForDoctor(OracleConnection& conn, int doctorId) {
    vector<RendezVous> appointments;
    string query = "SELECT rendezvous_id FROM RendezVous WHERE doctor_id = " + to_string(doctorId);
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

// Add a new consultation type to a doctor’s profile
bool DoctorController::addConsultationType(OracleConnection& conn, int doctorId, string consultationType) {
    string query = "INSERT INTO Doctor_Consultation_Types (doctor_id, consultation_type) VALUES (" +
    to_string(doctorId) + ", '" + consultationType + "')";
    try {
        conn.executeQuery(query);
        cout << "Consultation type added successfully." << endl;
        return true;
    } catch (...) {
        cout << "Failed to add consultation type." << endl;
        return false;
    }
}

// Get doctors by their category (e.g., dentist, optician)
vector<Doctor> DoctorController::getDoctorsByCategory(OracleConnection& conn, int categoryId) {
    vector<Doctor> doctors;
    string query = "SELECT doctor_id FROM Doctors WHERE categorie_id = " + to_string(categoryId);
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Doctor doctor;
        int id = stoi(row.at("DOCTOR_ID"));
        if (doctor.read(conn, id)) {
            doctors.push_back(doctor);
        }
    }
    return doctors;
}

// Get doctors by their city of practice
vector<Doctor> DoctorController::getDoctorsByCity(OracleConnection& conn, int cityId) {
    vector<Doctor> doctors;
    string query = "SELECT doctor_id FROM Doctors WHERE ville_id = " + to_string(cityId);
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Doctor doctor;
        int id = stoi(row.at("DOCTOR_ID"));
        if (doctor.read(conn, id)) {
            doctors.push_back(doctor);
        }
    }
    return doctors;
}

// Assign a doctor to a specific category (e.g., dentist, optician)
bool DoctorController::assignDoctorToCategory(OracleConnection& conn, int doctorId, int categoryId) {
    string query = "UPDATE Doctors SET categorie_id = " + to_string(categoryId) +
    " WHERE doctor_id = " + to_string(doctorId);
    try {
        conn.executeQuery(query);
        cout << "Doctor assigned to category successfully." << endl;
        return true;
    } catch (...) {
        cout << "Failed to assign doctor to category." << endl;
        return false;
    }
}

// Assign a doctor to a specific city
bool DoctorController::assignDoctorToCity(OracleConnection& conn, int doctorId, int cityId) {
    string query = "UPDATE Doctors SET ville_id = " + to_string(cityId) +
    " WHERE doctor_id = " + to_string(doctorId);
    try {
        conn.executeQuery(query);
        cout << "Doctor assigned to city successfully." << endl;
        return true;
    } catch (...) {
        cout << "Failed to assign doctor to city." << endl;
        return false;
    }
}

// Search for doctors by name
vector<Doctor> DoctorController::searchDoctorsByName(OracleConnection& conn, string name) {
    vector<Doctor> doctors;
    string query = "SELECT doctor_id FROM Doctors WHERE LOWER(nom) LIKE '%" + name + "%' OR LOWER(prenom) LIKE '%" + name + "%'";
    vector<map<string, string>> result = conn.executeQuery(query);

    for (const auto& row : result) {
        Doctor doctor;
        int id = stoi(row.at("DOCTOR_ID"));
        if (doctor.read(conn, id)) {
            doctors.push_back(doctor);
        }
    }
    return doctors;
}
