#include "patient_routes.h"

void setupPatientRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn) {
    PatientController patientController;

    // 1. Get all appointments for a given patient
    CROW_ROUTE(app, "/patient/<int>/appointments")
    ([&conn, &patientController](int patientId) {
        auto appointments = patientController.getAppointmentsForPatient(conn, patientId);
        crow::json::wvalue response;

        for (size_t i = 0; i < appointments.size(); ++i) {
            response[i]["id"] = appointments[i].getId();
            response[i]["temps"] = appointments[i].getTemps();
            response[i]["tarifs"] = appointments[i].getTarifs();
            response[i]["type_consultation"] = appointments[i].getTypeConsultation();
            response[i]["docteur_id"] = appointments[i].getDocteurId();
        }

        return response;
    });

    // 2. Schedule a new appointment for a patient
    CROW_ROUTE(app, "/patient/<int>/schedule_appointment").methods(crow::HTTPMethod::POST)
    ([&conn, &patientController](crow::request& req, crow::response& res, int patientId) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("temps") || !body.has("tarifs") || !body.has("type_consultation")) {
            res.code = 400;
            res.body = "Invalid input data.";
            return;  // Simply return void, res is automatically sent by Crow
        }

        std::string tmp = body["temps"].s();
        RendezVous appointment;
        appointment.setTemps(tmp);
        appointment.setTarifs(body["tarifs"].d());
        tmp = body["type_consultation"].s();
        appointment.setTypeConsultation(tmp);
        appointment.setPatientId(patientId);

        bool success = patientController.scheduleAppointment(conn, patientId, appointment);
        if (success) {
            res.code = 200;
            res.body = "Appointment scheduled successfully.";
        } else {
            res.code = 400;
            res.body = "Failed to schedule appointment.";
        }
        // No need to return res, Crow will automatically send the response
    });





    // 3. Search for patients by name
    CROW_ROUTE(app, "/patient/search/<string>")
    ([&conn, &patientController](const std::string& name) {
        auto patients = patientController.searchPatientsByName(conn, name);
        crow::json::wvalue response;

        for (size_t i = 0; i < patients.size(); ++i) {
            response[i]["id"] = patients[i].getId();
            response[i]["nom"] = patients[i].getNom();
            response[i]["prenom"] = patients[i].getPrenom();
            response[i]["date_of_birth"] = patients[i].getDateOfBirth(); // Assuming there's a date of birth accessor
        }

        return response;
    });

    // 4. Count the number of appointments for a patient
    CROW_ROUTE(app, "/patient/<int>/appointment_count")
    ([&conn, &patientController](int patientId) {
        int count = patientController.countAppointmentsForPatient(conn, patientId);
        crow::json::wvalue response;
        response["appointment_count"] = count;

        return response;
    });
}
