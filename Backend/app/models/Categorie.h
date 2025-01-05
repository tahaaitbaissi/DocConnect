#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <string>
#include "OracleConnection.h"

using namespace std;

class Categorie {
private:
    int id;
    string libelle;

public:
    Categorie();
    Categorie(int id, string libelle);
    ~Categorie();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    void deleteRecord(OracleConnection& conn);

    int getId();
    void setId(int id);
    string getLibelle();
    void setLibelle(string libelle);
};

#endif // CATEGORIE_H
