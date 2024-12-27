#ifndef SOINS_H
#define SOINS_H

#include <string>
#include "OracleConnection.h"

using namespace std;

class Soins {
private:
    int id;
    string libelle;

public:
    Soins();
    Soins(int id, string libelle);
    ~Soins();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    void deleteRecord(OracleConnection& conn);

    int getId();
    void setId(int id);
    string getLibelle();
    void setLibelle(string libelle);
};

#endif // SOINS_H
