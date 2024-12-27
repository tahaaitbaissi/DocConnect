#ifndef ADMINCONTROLLER_H_
#define ADMINCONTROLLER_H_

#include <vector>
#include "../models/User.h"
#include "../models/Doctor.h"
#include "../models/Patient.h"
#include "../models/OracleConnection.h"

using namespace std;

class AdminController {
public:
    AdminController();
    ~AdminController();

    // Admin Methods
    vector<User> getAllUsers(OracleConnection& conn);
    void deleteUser(OracleConnection& conn, int userId);
    vector<Doctor> getAllDoctors(OracleConnection& conn);
    void deleteDoctor(OracleConnection& conn, int doctorId);
    vector<Patient> getAllPatients(OracleConnection& conn);
    void deletePatient(OracleConnection& conn, int patientId);
    void updateDoctorDetails(OracleConnection& conn, int doctorId, string workHours, string description);
    void updatePatientDetails(OracleConnection& conn, int patientId, string dateOfBirth);
};

#endif // ADMINCONTROLLER_H_
