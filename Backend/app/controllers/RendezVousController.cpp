#include "RendezVousController.h"
#include <iostream>

RendezVousController::RendezVousController() {}
RendezVousController::~RendezVousController() {}

// Create a new appointment
bool RendezVousController::createAppointment(OracleConnection& conn, RendezVous rdv) {
    if (checkForConflictingAppointments(conn, rdv.getDocteurId(), rdv.getTemps())) {
        cout << "Appointment conflict detected. Please choose a different time." << endl;
        return false;
    }

    try {
        rdv.create(conn);
        cout << "Appointment created successfully." << endl;
        return true;
    } catch (...) {
        cout << "Failed to create appointment." << endl;
        return false;
    }
}

// Update an existing appointment
bool RendezVousController::updateAppointment(OracleConnection& conn, int appointmentId, string newTime, double newTariff) {
    string query = "UPDATE RendezVous SET temps = '" + newTime + "', tarifs = " +
    to_string(newTariff) + " WHERE rendezvous_id = " + to_string(appointmentId);
    try {
        conn.executeQuery(query);
        cout << "Appointment updated successfully." << endl;
        return true;
    } catch (...) {
        cout << "Failed to update appointment." << endl;
        return false;
    }
}

// Cancel an appointment
bool RendezVousController::cancelAppointment(OracleConnection& conn, int appointmentId) {
    string query = "DELETE FROM RendezVous WHERE rendezvous_id = " + to_string(appointmentId);
    try {
        conn.executeQuery(query);
        cout << "Appointment cancelled successfully." << endl;
        return true;
    } catch (...) {
        cout << "Failed to cancel appointment." << endl;
        return false;
    }
}

// Get all appointments for a specific patient
vector<RendezVous> RendezVousController::getAppointmentsForPatient(OracleConnection& conn, int patientId) {
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

// Get all appointments for a specific doctor
vector<RendezVous> RendezVousController::getAppointmentsForDoctor(OracleConnection& conn, int doctorId) {
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

// Get the details of a specific appointment
RendezVous RendezVousController::getAppointmentDetails(OracleConnection& conn, int appointmentId) {
    RendezVous appointment;
    if (appointment.read(conn, appointmentId)) {
        return appointment;
    }
    throw runtime_error("Appointment not found.");
}

// Check if an appointment conflicts with another one
bool RendezVousController::checkForConflictingAppointments(OracleConnection& conn, int doctorId, string time) {
    string query = "SELECT * FROM RendezVous WHERE doctor_id = " + to_string(doctorId) +
    " AND temps = '" + time + "'";
    vector<map<string, string>> result = conn.executeQuery(query);
    return !result.empty();
}

// Get appointments by consultation type (e.g., "domicile", "video", "cabinet")
vector<RendezVous> RendezVousController::getAppointmentsByConsultationType(OracleConnection& conn, string consultationType) {
    vector<RendezVous> appointments;
    string query = "SELECT rendezvous_id FROM RendezVous WHERE type_consultation = '" + consultationType + "'";
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
