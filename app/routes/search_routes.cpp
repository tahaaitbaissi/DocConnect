#include "search_routes.h"

void setupSearchRoutes(crow::SimpleApp& app, OracleConnection& conn) {
    SearchController searchController;

    // Route to search doctors by name
    CROW_ROUTE(app, "/search/doctors/<string>")
    ([&conn, &searchController](const std::string& name) {
        auto doctors = searchController.searchDoctorsByName(conn, name);
        crow::json::wvalue response;

        for (size_t i = 0; i < doctors.size(); ++i) {
            response[i]["id"] = doctors[i].getId();
            response[i]["nom"] = doctors[i].getNom();
            response[i]["prenom"] = doctors[i].getPrenom();
            response[i]["email"] = doctors[i].getEmail();
            response[i]["adresse"] = doctors[i].getAdresse();
            response[i]["telephone"] = doctors[i].getTelephone();
            response[i]["sexe"] = doctors[i].getSexe();
            response[i]["work_hours"] = doctors[i].getWorkHours();
            response[i]["description"] = doctors[i].getDescription();
            response[i]["consultation_type"] = doctors[i].getConsultationType();
            response[i]["categorie_id"] = doctors[i].getCategorieId();
            response[i]["ville_id"] = doctors[i].getVilleId();
        }

        return response;
    });

    // Route to search patients by name
    CROW_ROUTE(app, "/search/patients/<string>")
    ([&conn, &searchController](const std::string& name) {
        auto patients = searchController.searchPatientsByName(conn, name);
        crow::json::wvalue response;

        for (size_t i = 0; i < patients.size(); ++i) {
            response[i]["id"] = patients[i].getId();
            response[i]["nom"] = patients[i].getNom();
            response[i]["prenom"] = patients[i].getPrenom();
            response[i]["email"] = patients[i].getEmail();
            response[i]["adresse"] = patients[i].getAdresse();
            response[i]["telephone"] = patients[i].getTelephone();
            response[i]["sexe"] = patients[i].getSexe();
            response[i]["date_of_birth"] = patients[i].getDateOfBirth();
        }

        return response;
    });

    // Route to search appointments by doctor ID
    CROW_ROUTE(app, "/search/appointments/doctor/<int>")
    ([&conn, &searchController](int doctorId) {
        auto appointments = searchController.searchAppointmentsByDoctor(conn, doctorId);
        crow::json::wvalue response;

        for (size_t i = 0; i < appointments.size(); ++i) {
            response[i]["id"] = appointments[i].getId();
            response[i]["temps"] = appointments[i].getTemps();
            response[i]["tarifs"] = appointments[i].getTarifs();
            response[i]["type_consultation"] = appointments[i].getTypeConsultation();
            response[i]["patient_id"] = appointments[i].getPatientId();
            response[i]["docteur_id"] = appointments[i].getDocteurId();
        }

        return response;
    });

    // Route to search appointments by patient ID
    CROW_ROUTE(app, "/search/appointments/patient/<int>")
    ([&conn, &searchController](int patientId) {
        auto appointments = searchController.searchAppointmentsByPatient(conn, patientId);
        crow::json::wvalue response;

        for (size_t i = 0; i < appointments.size(); ++i) {
            response[i]["id"] = appointments[i].getId();
            response[i]["temps"] = appointments[i].getTemps();
            response[i]["tarifs"] = appointments[i].getTarifs();
            response[i]["type_consultation"] = appointments[i].getTypeConsultation();
            response[i]["patient_id"] = appointments[i].getPatientId();
            response[i]["docteur_id"] = appointments[i].getDocteurId();
        }

        return response;
    });

    // Route to search doctors by category ID
    CROW_ROUTE(app, "/search/doctors/category/<int>")
    ([&conn, &searchController](int categoryId) {
        auto doctors = searchController.searchDoctorsByCategory(conn, categoryId);
        crow::json::wvalue response;

        for (size_t i = 0; i < doctors.size(); ++i) {
            response[i]["id"] = doctors[i].getId();
            response[i]["nom"] = doctors[i].getNom();
            response[i]["prenom"] = doctors[i].getPrenom();
            response[i]["email"] = doctors[i].getEmail();
            response[i]["adresse"] = doctors[i].getAdresse();
            response[i]["telephone"] = doctors[i].getTelephone();
            response[i]["sexe"] = doctors[i].getSexe();
            response[i]["work_hours"] = doctors[i].getWorkHours();
            response[i]["description"] = doctors[i].getDescription();
            response[i]["consultation_type"] = doctors[i].getConsultationType();
            response[i]["categorie_id"] = doctors[i].getCategorieId();
            response[i]["ville_id"] = doctors[i].getVilleId();
        }

        return response;
    });

    // Route to search doctors by city ID
    CROW_ROUTE(app, "/search/doctors/city/<int>")
    ([&conn, &searchController](int cityId) {
        auto doctors = searchController.searchDoctorsByCity(conn, cityId);
        crow::json::wvalue response;

        for (size_t i = 0; i < doctors.size(); ++i) {
            response[i]["id"] = doctors[i].getId();
            response[i]["nom"] = doctors[i].getNom();
            response[i]["prenom"] = doctors[i].getPrenom();
            response[i]["email"] = doctors[i].getEmail();
            response[i]["adresse"] = doctors[i].getAdresse();
            response[i]["telephone"] = doctors[i].getTelephone();
            response[i]["sexe"] = doctors[i].getSexe();
            response[i]["work_hours"] = doctors[i].getWorkHours();
            response[i]["description"] = doctors[i].getDescription();
            response[i]["consultation_type"] = doctors[i].getConsultationType();
            response[i]["categorie_id"] = doctors[i].getCategorieId();
            response[i]["ville_id"] = doctors[i].getVilleId();
        }

        return response;
    });
}
