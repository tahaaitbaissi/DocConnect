#include "Ville.h"
#include <iostream>

using namespace std;

Ville::Ville() : id(0), nom("") {}
Ville::Ville(int id, string nom) : id(id), nom(nom) {}

Ville::~Ville() {}

void Ville::create(OracleConnection& conn) {
    string query = "INSERT INTO Villes (ville_id, nom) VALUES (seq_villes.NEXTVAL, '" + nom + "')";
    conn.executeQuery(query);

    this->id = conn.getGeneratedId("seq_villes");
}

bool Ville::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Villes WHERE ville_id = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        map<string, string> row = result[0];
        this->id = id;
        nom = row["NOM"];
        return true;
    }
    return false;
}

void Ville::update(OracleConnection& conn) {
    string query = "UPDATE Villes SET nom = '" + nom + "' WHERE ville_id = " + to_string(id);
    conn.executeQuery(query);
}

void Ville::deleteRecord(OracleConnection& conn) {
    string query = "DELETE FROM Villes WHERE ville_id = " + to_string(id);
    conn.executeQuery(query);
}

int Ville::getId() { return id; }
void Ville::setId(int id) { this->id = id; }
string Ville::getNom() { return nom; }
void Ville::setNom(string nom) { this->nom = nom; }
