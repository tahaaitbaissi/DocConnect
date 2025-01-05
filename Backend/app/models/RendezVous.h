#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <string>
#include "OracleConnection.h"

using namespace std;

class RendezVous {
private:
    int id;
    string temps;
    double tarifs;
    string typeConsultation; // Should match the enum 'domicile', 'video',
                             //'cabinet'
    int patientId;
    int docteurId;

public:
    RendezVous();
    RendezVous(int id, string temps, double tarifs,  string typeConsultation, int patientId, int docteurId);
    ~RendezVous();

    // CRUD Methods
    void create(OracleConnection& conn);
    bool read(OracleConnection& conn, int id);
    void update(OracleConnection& conn);
    void deleteRecord(OracleConnection& conn);

    // Getters and Setters
    int getId();
    void setId(int id);
    string getTemps();
    void setTemps( string& temps);
    double getTarifs();
    void setTarifs(double tarifs);
    string getTypeConsultation();
    void setTypeConsultation( string& typeConsultation);
    int getPatientId();
    void setPatientId(int patientId);
    int getDocteurId();
    void setDocteurId(int docteurId);
};

#endif // RENDEZVOUS_H
