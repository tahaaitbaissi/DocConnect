#include "doctor_routes.h"

void setupDoctorRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn) {
    DoctorController doctorController;

    // 1. Get all appointments for a specific doctor
    CROW_ROUTE(app, "/doctor/<int>/appointments")
    ([&conn, &doctorController](int doctorId) {
        auto appointments = doctorController.getAppointmentsForDoctor(conn, doctorId);
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

    // 2. Get doctors by their category (e.g., dentist, optician)
    CROW_ROUTE(app, "/doctor/category/<int>")
    ([&conn, &doctorController](int categoryId) {
        auto doctors = doctorController.getDoctorsByCategory(conn, categoryId);
        crow::json::wvalue response;

        for (size_t i = 0; i < doctors.size(); ++i) {
            response[i]["id"] = doctors[i].getId();
            response[i]["nom"] = doctors[i].getNom();
            response[i]["prenom"] = doctors[i].getPrenom();
            response[i]["work_hours"] = doctors[i].getWorkHours(); // Assuming work hours is available
        }

        return response;
    });

    // 3. Get doctors by their city of practice
    CROW_ROUTE(app, "/doctor/city/<int>")
    ([&conn, &doctorController](int cityId) {
        auto doctors = doctorController.getDoctorsByCity(conn, cityId);
        crow::json::wvalue response;

        for (size_t i = 0; i < doctors.size(); ++i) {
            response[i]["id"] = doctors[i].getId();
            response[i]["nom"] = doctors[i].getNom();
            response[i]["prenom"] = doctors[i].getPrenom();
        }

        return response;
    });

    // 4. Assign a doctor to a specific category
    CROW_ROUTE(app, "/doctor/<int>/assign_category/<int>").methods(crow::HTTPMethod::PUT)
    ([&conn, &doctorController](int doctorId, int categoryId) {
        bool success = doctorController.assignDoctorToCategory(conn, doctorId, categoryId);
        if (success) {
            return crow::response(200, "Doctor assigned to category successfully.");
        } else {
            return crow::response(400, "Failed to assign doctor to category.");
        }
    });

    // 5. Assign a doctor to a specific city
    CROW_ROUTE(app, "/doctor/<int>/assign_city/<int>").methods(crow::HTTPMethod::PUT)
    ([&conn, &doctorController](int doctorId, int cityId) {
        bool success = doctorController.assignDoctorToCity(conn, doctorId, cityId);
        if (success) {
            return crow::response(200, "Doctor assigned to city successfully.");
        } else {
            return crow::response(400, "Failed to assign doctor to city.");
        }
    });

    // 6. Search for doctors by name
    CROW_ROUTE(app, "/doctor/search/<string>")
    ([&conn, &doctorController](const std::string& name) {
        auto doctors = doctorController.searchDoctorsByName(conn, name);
        crow::json::wvalue response;

        for (size_t i = 0; i < doctors.size(); ++i) {
            response[i]["id"] = doctors[i].getId();
            response[i]["nom"] = doctors[i].getNom();
            response[i]["prenom"] = doctors[i].getPrenom();
            response[i]["work_hours"] = doctors[i].getWorkHours();  // Assuming work hours available
        }

        return response;
    });
}
