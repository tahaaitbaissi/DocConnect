#ifndef SEARCHCONTROLLER_H_
#define SEARCHCONTROLLER_H_

#include <vector>
#include <string>
#include "../models/Doctor.h"
#include "../models/Patient.h"
#include "../models/Rendezvous.h"
#include "../models/OracleConnection.h"

using namespace std;

class SearchController {
public:
    SearchController();
    ~SearchController();

    // Search Methods
    vector<Doctor> searchDoctorsByName(OracleConnection& conn, string name);
    vector<Patient> searchPatientsByName(OracleConnection& conn, string name);
    vector<Rendezvous> searchAppointmentsByDoctor(OracleConnection& conn, int doctorId);
    vector<Rendezvous> searchAppointmentsByPatient(OracleConnection& conn, int patientId);
    vector<Doctor> searchDoctorsByCategory(OracleConnection& conn, int categoryId);
    vector<Doctor> searchDoctorsByCity(OracleConnection& conn, int cityId);
};

#endif // SEARCHCONTROLLER_H_
