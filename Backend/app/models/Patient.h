#ifndef PATIENT_H_
#define PATIENT_H_

#include <string>
#include "User.h"
#include "OracleConnection.h"

using namespace std;

class Patient : public User {
private:
    string dateOfBirth; // Corresponds to date_naissance in the Users table

public:
    Patient();
    Patient(int userId, string nom, string prenom, string email,
            string password, string adresse, string telephone, string sexe,
            string dateOfBirth);
    ~Patient();

    // CRUD Methods
    void create(OracleConnection& conn); // Creates entries in Users (Patient-specific data)
    bool read(OracleConnection& conn, int userId); // Reads from Users (Patient-specific data)
    void update(OracleConnection& conn); // Updates Users (Patient-specific data)
    void deleteRecord(OracleConnection& conn); // Deletes from Users (Patient-specific data)

    // Getters and Setters
    string getDateOfBirth();
    void setDateOfBirth(string dateOfBirth);
};

#endif // PATIENT_H_
