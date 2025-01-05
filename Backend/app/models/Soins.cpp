#include "Soins.h"
#include <iostream>

using namespace std;

Soins::Soins() : id(0), libelle(""), categorieId(0) {}

Soins::Soins(int id, string libelle, int categorieId) : id(id), libelle(libelle), categorieId(categorieId) {}

Soins::~Soins() {}

void Soins::create(OracleConnection& conn) {
    string query = "INSERT INTO Soins (soin_id, libelle, categorie_id) VALUES (seq_soins.NEXTVAL, '" + libelle + "', " + to_string(categorieId) + ")";
    conn.executeQuery(query);

    this->id = conn.getGeneratedId("seq_soins");
}

bool Soins::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Soins WHERE soin_id = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        map<string, string> row = result[0];
        this->id = id;
        libelle = row["LIBELLE"];
        categorieId = stoi(row["CATEGORIE_ID"]);  // Fetch categorieId
        return true;
    }
    return false;
}

void Soins::update(OracleConnection& conn) {
    string query = "UPDATE Soins SET libelle = '" + libelle + "', categorie_id = " + to_string(categorieId) + " WHERE soin_id = " + to_string(id);
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
int Soins::getCategorieId() { return categorieId; }  // Getter for categorieId
void Soins::setCategorieId(int categorieId) { this->categorieId = categorieId; }  // Setter for categorieId
