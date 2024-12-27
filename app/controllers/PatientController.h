#ifndef PATIENTCONTROLLER_H_
#define PATIENTCONTROLLER_H_

#include <vector>
#include <string>
#include "../models/Patient.h"
#include "../models/RendezVous.h"
#include "../models/OracleConnection.h"

using namespace std;

class PatientController {
public:
    PatientController();
    ~PatientController();

    vector<RendezVous> getAppointmentsForPatient(OracleConnection& conn, int patientId);
    bool scheduleAppointment(OracleConnection& conn, int patientId, RendezVous& appointment);
    vector<Patient> searchPatientsByName(OracleConnection& conn, string name);
    int countAppointmentsForPatient(OracleConnection& conn, int patientId);
};

#endif // PATIENTCONTROLLER_H_
