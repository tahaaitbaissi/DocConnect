#include "rendezvous_routes.h"

void setupRendezVousRoutes(crow::SimpleApp& app, OracleConnection& conn) {
    RendezVousController rendezVousController;

    // 1. Create a new appointment
    CROW_ROUTE(app, "/rendezvous/create").methods(crow::HTTPMethod::POST)
    ([&conn, &rendezVousController](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("doctor_id") || !body.has("patient_id") || !body.has("time") ||
            !body.has("tariff") || !body.has("consultation_type")) {
            return crow::response(400, "Invalid input data.");
            }

            int doctorId = body["doctor_id"].i();
        int patientId = body["patient_id"].i();
        string time = body["time"].s();
        double tariff = body["tariff"].d();
        string consultationType = body["consultation_type"].s();

        bool success = rendezVousController.createAppointment(conn, doctorId, patientId, time, tariff, consultationType);
        if (success) {
            return crow::response(200, "Appointment created successfully.");
        } else {
            return crow::response(400, "Failed to create appointment.");
        }
    });

    // 2. Update an existing appointment
    CROW_ROUTE(app, "/rendezvous/update/<int>").methods(crow::HTTPMethod::POST)
    ([&conn, &rendezVousController](const crow::request& req, crow::response& res, int appointmentId) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("new_time") || !body.has("new_tariff")) {
            res.code = 400;
            res.body = "Invalid input data.";
            return;  // Just return, as we directly modify the response.
        }

        string newTime = body["new_time"].s();
        double newTariff = body["new_tariff"].d();

        bool success = rendezVousController.updateAppointment(conn, appointmentId, newTime, newTariff);
        if (success) {
            res.code = 200;
            res.body = "Appointment updated successfully.";
        } else {
            res.code = 400;
            res.body = "Failed to update appointment.";
        }
        return;  // No need to return a response, it's set through the res object.
    });



    // 3. Cancel an appointment
    CROW_ROUTE(app, "/rendezvous/cancel/<int>").methods(crow::HTTPMethod::POST)
    ([&conn, &rendezVousController](int appointmentId) {
        bool success = rendezVousController.cancelAppointment(conn, appointmentId);
        if (success) {
            return crow::response(200, "Appointment cancelled successfully.");
        } else {
            return crow::response(400, "Failed to cancel appointment.");
        }
    });

    // 4. Get all appointments for a specific patient
    CROW_ROUTE(app, "/rendezvous/patient/<int>").methods(crow::HTTPMethod::GET)
    ([&conn, &rendezVousController](int patientId) {
        auto appointments = rendezVousController.getAppointmentsForPatient(conn, patientId);
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

    // 5. Get all appointments for a specific doctor
    CROW_ROUTE(app, "/rendezvous/doctor/<int>").methods(crow::HTTPMethod::GET)
    ([&conn, &rendezVousController](int doctorId) {
        auto appointments = rendezVousController.getAppointmentsForDoctor(conn, doctorId);
        crow::json::wvalue response;

        for (size_t i = 0; i < appointments.size(); ++i) {
            response[i]["id"] = appointments[i].getId();
            response[i]["temps"] = appointments[i].getTemps();
            response[i]["tarifs"] = appointments[i].getTarifs();
            response[i]["type_consultation"] = appointments[i].getTypeConsultation();
            response[i]["patient_id"] = appointments[i].getPatientId();
        }

        return response;
    });

    // 6. Get details of a specific appointment
    CROW_ROUTE(app, "/rendezvous/details/<int>").methods(crow::HTTPMethod::GET)
    ([&conn, &rendezVousController](int appointmentId) {
        try {
            auto appointment = rendezVousController.getAppointmentDetails(conn, appointmentId);
            crow::json::wvalue response;
            response["id"] = appointment.getId();
            response["temps"] = appointment.getTemps();
            response["tarifs"] = appointment.getTarifs();
            response["type_consultation"] = appointment.getTypeConsultation();
            response["docteur_id"] = appointment.getDocteurId();
            response["patient_id"] = appointment.getPatientId();
            return crow::response(200, response);  // Return the response with the JSON body
        } catch (...) {
            crow::json::wvalue errorResponse;
            errorResponse["error"] = "Appointment not found.";
            return crow::response(404, errorResponse);  // Return a 404 response with the error message
        }
    });


    // 7. Get appointments by consultation type
    CROW_ROUTE(app, "/rendezvous/consultation_type/<string>").methods(crow::HTTPMethod::GET)
    ([&conn, &rendezVousController](const std::string& consultationType) {
        auto appointments = rendezVousController.getAppointmentsByConsultationType(conn, consultationType);
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
}
