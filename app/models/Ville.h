#ifndef VILLE_H
#define VILLE_H

#include <string>
#include "OracleConnection.h"

using namespace std;

class Ville {
private:
    int id;
    string nom;

public:
    Ville();
    Ville(int id, string nom);
    ~Ville();

    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    void deleteRecord(OracleConnection& conn);

    int getId();
    void setId(int id);
    string getNom();
    void setNom(string nom);
};

#endif // VILLE_H
