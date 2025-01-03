#ifndef DOCTORCONTROLLER_H_
#define DOCTORCONTROLLER_H_

#include <vector>
#include <string>
#include "../models/Doctor.h"
#include "../models/RendezVous.h"
#include "../models/OracleConnection.h"
#include "../models/Categorie.h"
#include "../models/Ville.h"
// s
using namespace std;

class DoctorController {
public:
    DoctorController();
    ~DoctorController();

    // Functionality
    vector<RendezVous> getAppointmentsForDoctor(OracleConnection& conn, int doctorId);
    vector<Doctor> getDoctorsByCategory(OracleConnection& conn, int categoryId);
    vector<Doctor> getDoctorsByCity(OracleConnection& conn, int cityId);
    bool assignDoctorToCategory(OracleConnection& conn, int doctorId, int categoryId);
    bool assignDoctorToCity(OracleConnection& conn, int doctorId, int cityId);
    vector<Doctor> searchDoctorsByName(OracleConnection& conn, string name);
};

#endif // DOCTORCONTROLLER_H_
