#include "User.h"

#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

User::User() : id(0), nom(""), prenom(""), email(""), password(""), adresse(""), telephone(""), sexe("") {}
User::User(int id, const string& nom, const string& prenom, const string& email,
           const string& password, const string& adresse, const string& telephone, const string& sexe)
    : id(id), nom(nom), prenom(prenom), email(email), password(password), adresse(adresse), telephone(telephone), sexe(sexe) {}

User::~User() {}

void User::create(OracleConnection& conn) {
    cout << "id : " <<  to_string(id) << endl;
    string query = "INSERT INTO Users (user_id, nom, prenom, email, password, adresse, telephone, sexe) VALUES ('" + 
                         to_string(id) + "', '" + 
                         nom + "', '" + prenom + "', '" + email + "', '" + password + "', '" + adresse + "', '" +
                         telephone + "', '" + sexe + "')";
    conn.executeQuery(query);
}

bool User::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Users WHERE user_id = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        map<string, string> row = result[0];
        this->id = id;
        nom = row["NOM"];
        prenom = row["PRENOM"];
        email = row["EMAIL"];
        password = row["PASSWORD"];
        adresse = row["ADRESSE"];
        telephone = row["TELEPHONE"];
        sexe = row["SEXE"];
        return true;
    }
    return false;
}

void User::update(OracleConnection& conn) {
    string query = "UPDATE Users SET nom = '" + nom + "', prenom = '" + prenom + "', email = '" + email +
                         "', password = '" + password + "', adresse = '" + adresse + "', telephone = '" + telephone +
                         "', sexe = '" + sexe + "' WHERE user_id = " + to_string(id);
    conn.executeQuery(query);
}

void User::deleteRecord(OracleConnection& conn) {
    string query = "DELETE FROM Users WHERE user_id = " + to_string(id);
    conn.executeQuery(query);
}

int User::getId() const { return id; }
void User::setId(int id) { this->id = id; }
string User::getNom() const { return nom; }
void User::setNom(const string& nom) { this->nom = nom; }
string User::getEmail() const { return email; }
void User::setEmail(const string& email) { this->email = email; }
// Add similar methods for other attributes...
