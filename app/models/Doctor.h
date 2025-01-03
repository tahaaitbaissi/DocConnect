#ifndef DOCTOR_H_
#define DOCTOR_H_

#include <string>
#include <vector>
#include "User.h"
#include "OracleConnection.h"

using namespace std;

class Doctor : public User {
private:
    string workHours;         // Corresponds to heure_travail in the Users table
    string description;       // Doctor's description
    string consultationType;  // Single consultation type, e.g., "domicile", "video", "cabinet"
    int categorieId;          // Foreign key to Categories
    int villeId;              // Foreign key to Ville

public:
    Doctor();
    Doctor(int userId, string nom, string prenom, string email,
           string password, string adresse, string telephone, string sexe,
           string workHours, string description, string consultationType,
           int categorieId, int villeId);
    ~Doctor();

    // CRUD Methods
    void create(OracleConnection& conn); // Creates entries in Users (Doctor-specific data)
    bool read(OracleConnection& conn, int userId); // Reads from Users (Doctor-specific data)
    void update(OracleConnection& conn); // Updates Users (Doctor-specific data)
    void deleteRecord(OracleConnection& conn); // Deletes from Users (Doctor-specific data)

    // Getters and Setters
    string getWorkHours();
    void setWorkHours(string workHours);
    string getDescription();
    void setDescription(string description);
    string getConsultationType();
    void setConsultationType(string consultationType);
    int getCategorieId();
    void setCategorieId(int categorieId);
    int getVilleId();
    void setVilleId(int villeId);
};

#endif // DOCTOR_H_
