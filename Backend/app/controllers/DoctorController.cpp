#include "DoctorController.h"
#include <iostream>

DoctorController::DoctorController() {}
DoctorController::~DoctorController() {}

// Get all appointments for a specific doctor
vector<RendezVous> DoctorController::getAppointmentsForDoctor(OracleConnection& conn, int doctorId) {
    vector<RendezVous> appointments;
    string query = "SELECT rendezvous_id FROM Rendezvous WHERE doctor_id = " + to_string(doctorId);
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

// Get doctors by their category (e.g., dentist, optician)
vector<Doctor> DoctorController::getDoctorsByCategory(OracleConnection& conn, int categoryId) {
    vector<Doctor> doctors;
    string query = "SELECT user_id FROM Users WHERE categorie_id = " + to_string(categoryId);
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
    string query = "SELECT user_id FROM Users WHERE ville_id = " + to_string(cityId);
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
    string query = "UPDATE Users SET categorie_id = " + to_string(categoryId) +
    " WHERE users_id = " + to_string(doctorId);
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
    string query = "UPDATE Users SET ville_id = " + to_string(cityId) +
    " WHERE user_id = " + to_string(doctorId);
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
    string query = "SELECT user_id FROM Users WHERE LOWER(nom) LIKE '%" + name + "%' OR LOWER(prenom) LIKE '%" + name + "%'";
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

bool DoctorController::addSoinsToDoctor(OracleConnection& conn, int doctorId, vector<int>& soinIds) {
    try {
        // Loop through all soins IDs and add them to the Doctor_Soins pivot table
        for (int soinId : soinIds) {
            Doctor doctor;
            if (doctor.read(conn, doctorId)) {
                doctor.addSoin(conn, soinId);
            } else {
                return false;  // If doctor doesn't exist, return false
            }
        }
        return true;  // Successfully added all soins
    } catch (const std::exception& e) {
        cout << "Error adding soins to doctor: " << e.what() << endl;
        return false;
    }
}

