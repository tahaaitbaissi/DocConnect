#include "Categorie.h"
#include <iostream>

using namespace std;

Categorie::Categorie() : id(0), libelle("") {}
Categorie::Categorie(int id, string libelle) : id(id), libelle(libelle) {}

Categorie::~Categorie() {}

void Categorie::create(OracleConnection& conn) {
    string query = "INSERT INTO Categories (categorie_id, libelle) VALUES (seq_categories.NEXTVAL, '" + libelle + "')";
    conn.executeQuery(query);

    this->id = conn.getGeneratedId("seq_categories");
}

bool Categorie::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM Categories WHERE categorie_id = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        map<string, string> row = result[0];
        this->id = id;
        libelle = row["LIBELLE"];
        return true;
    }
    return false;
}

void Categorie::update(OracleConnection& conn) {
    string query = "UPDATE Categories SET libelle = '" + libelle + "' WHERE categorie_id = " + to_string(id);
    conn.executeQuery(query);
}

void Categorie::deleteRecord(OracleConnection& conn) {
    string query = "DELETE FROM Categories WHERE categorie_id = " + to_string(id);
    conn.executeQuery(query);
}

int Categorie::getId() { return id; }
void Categorie::setId(int id) { this->id = id; }
string Categorie::getLibelle() { return libelle; }
void Categorie::setLibelle( string libelle) { this->libelle = libelle; }
