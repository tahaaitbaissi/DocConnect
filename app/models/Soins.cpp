#include "Soins.h"
#include <iostream>

using namespace std;

Soins::Soins() : id(0), libelle("") {}
Soins::Soins(int id, string libelle) : id(id), libelle(libelle) {}

Soins::~Soins() {}

void Soins::create(OracleConnection& conn) {
    string query = "INSERT INTO Soins (soin_id, libelle) VALUES ('" + to_string(id) + "', '" + libelle + "')";
    conn.executeQuery(query);
}

bool Soins::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Soins WHERE soin_id = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        map<string, string> row = result[0];
        this->id = id;
        libelle = row["LIBELLE"];
        return true;
    }
    return false;
}

void Soins::update(OracleConnection& conn) {
    string query = "UPDATE Soins SET libelle = '" + libelle + "' WHERE soin_id = " + to_string(id);
    conn.executeQuery(query);
}

void Soins::deleteRecord(OracleConnection& conn) {
    string query = "DELETE FROM Soins WHERE soin_id = " + to_string(id);
    conn.executeQuery(query);
}

int Soins::getId() { return id; }
void Soins::setId(int id) { this->id = id; }
string Soins::getLibelle() { return libelle; }
void Soins::setLibelle(string libelle) { this->libelle = libelle; }
