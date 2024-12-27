#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "OracleConnection.h"

using namespace std;

class User {
protected:
    int id;
    string nom;
    string prenom;
    string email;
    string password;
    string adresse;
    string telephone;
    string sexe;

public:
    User();
    User(int id, const string& nom, const string& prenom, const string& email,
         const string& password, const string& adresse, const string& telephone, const string& sexe);
    virtual ~User();

    // CRUD Methods
    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    void deleteRecord(OracleConnection& conn);

    // Getters and Setters
    int getId() const;
    void setId(int id);
    string getNom() const;
    void setNom(const string& nom);
    string getEmail() const;
    void setEmail(const string& nom);

    // Add similar methods for other attributes...
};

#endif // USER_H
