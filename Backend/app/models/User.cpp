#include "User.h"

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

User::User() : id(0), nom(""), prenom(""), email(""), password(""), adresse(""), telephone(""), sexe("") {}

User::User(int id, string nom, string prenom, string email,
           string password, string adresse, string telephone, string sexe)
: id(id), nom(nom), prenom(prenom), email(email), password(password), adresse(adresse), telephone(telephone), sexe(sexe) {}

User::~User() {}
//
void User::create(OracleConnection& conn) {
    string query = "INSERT INTO Users (user_id, nom, prenom, email, password, adresse, telephone, sexe, role) "
    "VALUES (SEQ_USERS.NEXTVAL, '" + nom + "', '" + prenom + "', '" + email + "', '" + password + "', '"
    + adresse + "', '" + telephone + "', '" + sexe + "', '"+ role +"')";
    conn.executeQuery(query);

    this->id = conn.getGeneratedId("seq_users");
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
        role = row["ROLE"];
        return true;
    }
    return false;
}


void User::update(OracleConnection& conn) {
    // Using concatenation for the SQL query string
    string query = "UPDATE Users SET nom = '" + nom + "', prenom = '" + prenom + "', email = '" + email +
    "', password = '" + password + "', adresse = '" + adresse + "', telephone = '" + telephone +
    "', sexe = '" + sexe + "' WHERE user_id = " + to_string(id);
    conn.executeQuery(query);
}

void User::deleteRecord(OracleConnection& conn) {
    string query = "DELETE FROM Users WHERE user_id = " + to_string(id);
    conn.executeQuery(query);
}

int User::getId() { return id; }
void User::setId(int id) { this->id = id; }

string User::getNom() { return nom; }
void User::setNom(string nom) { this->nom = nom; }

string User::getPrenom() { return prenom; }
void User::setPrenom(string prenom) { this->prenom = prenom; }

string User::getEmail() { return email; }
void User::setEmail(string email) { this->email = email; }

string User::getPassword() { return password; }
void User::setPassword(string password) { this->password = password; }

string User::getAdresse() { return adresse; }
void User::setAdresse(string adresse) { this->adresse = adresse; }

string User::getTelephone() { return telephone; }
void User::setTelephone(string telephone) { this->telephone = telephone; }

string User::getSexe() { return sexe; }
void User::setSexe(string sexe) { this->sexe = sexe; }

string User::getRole() {
    return role;
}

void User::setRole(string r) {
    role = r;
}
