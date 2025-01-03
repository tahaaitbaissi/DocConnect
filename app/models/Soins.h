#ifndef SOINS_H
#define SOINS_H

#include <string>
#include "OracleConnection.h"

using namespace std;

class Soins {
private:
    int id;
    string libelle;
    int categorieId;  // Foreign key to Categories

public:
    Soins();
    Soins(int id, string libelle, int categorieId);  // Updated constructor
    ~Soins();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    void deleteRecord(OracleConnection& conn);

    int getId();
    void setId(int id);
    string getLibelle();
    void setLibelle(string libelle);
    int getCategorieId();  // Getter for categorieId
    void setCategorieId(int categorieId);  // Setter for categorieId
};

#endif // SOINS_H
