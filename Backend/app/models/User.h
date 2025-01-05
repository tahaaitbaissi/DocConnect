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
    string role;

public:
    User();
    User(int id, string nom, string prenom, string email,
         string password, string adresse, string telephone, string sexe);
    virtual ~User();

    // CRUD Methods
    virtual void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    void deleteRecord(OracleConnection& conn);

    // Getters and Setters
    int getId();
    void setId(int id);
    string getNom();
    void setNom(string nom);
    string getPrenom();
    void setPrenom(string prenom);
    string getEmail();
    void setEmail(string email);
    string getPassword();
    void setPassword(string password);
    string getAdresse();
    void setAdresse(string adresse);
    string getTelephone();
    void setTelephone(string telephone);
    string getSexe();
    void setSexe(string sexe);

    string getRole();
    void setRole(string r);
};

#endif // USER_H
