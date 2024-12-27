#ifndef PATIENT_H_
#define PATIENT_H_

#include <string>
#include "User.h"
#include "OracleConnection.h"

using namespace std;

class Patient : public User {
private:
    int patientId;      // ID specific to the Patients table
    string dateOfBirth; // Corresponds to date_naissance in the Patients table

public:
    Patient();
    Patient(int userId, int patientId, string nom, string prenom, string email,
            string password, string adresse, string telephone, string sexe,
            string dateOfBirth);
    ~Patient();

    // CRUD Methods
    void create(OracleConnection& conn); // Creates entries in both Users and Patients
    bool read(OracleConnection& conn, int patientId); // Reads from both Users and Patients
    void update(OracleConnection& conn); // Updates both Users and Patients
    void deleteRecord(OracleConnection& conn); // Deletes from both Users and Patients

    // Getters and Setters
    int getPatientId();
    void setPatientId(int patientId);
    string getDateOfBirth();
    void setDateOfBirth(string dateOfBirth);
};

#endif // PATIENT_H_
