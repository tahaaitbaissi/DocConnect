#include "RendezVous.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

RendezVous::RendezVous() : id(0), temps(""), tarifs(0.0), typeConsultation(""), patientId(0), docteurId(0) {}

RendezVous::RendezVous(int id, string temps, double tarifs, string typeConsultation, int patientId, int docteurId)
: id(id), temps(temps), tarifs(tarifs), typeConsultation(typeConsultation), patientId(patientId), docteurId(docteurId) {}

RendezVous::~RendezVous() {}

void RendezVous::create(OracleConnection& conn) {
    string query = "INSERT INTO RENDEZVOUS (RENDEZVOUS_ID, temps, tarifs, type_consultation, patient_id, docteur_id) VALUES (seq_rendezvous.NEXTVAL, '" + temps + "', '" + to_string(tarifs) + "', '" +
    typeConsultation + "', '" + to_string(patientId) + "', '" + to_string(docteurId) + "')";
    conn.executeQuery(query);

    this->id = conn.getGeneratedId("seq_rendezvous");
}

bool RendezVous::read(OracleConnection& conn, int id) {
    string query = "SELECT * FROM RENDEZVOUS WHERE RENDEZVOUS_ID = " + to_string(id);
    vector<map<string, string>> result = conn.executeQuery(query);
    if (!result.empty()) {
        map<string, string> row = result[0];
        this->id = id;
        temps = row["TEMPS"];
        tarifs = stod(row["TARIFS"]);
        typeConsultation = row["TYPE_CONSULTATION"];
        patientId = stoi(row["PATIENT_ID"]);
        docteurId = stoi(row["DOCTEUR_ID"]);
        return true;
    }
    return false;
}

void RendezVous::update(OracleConnection& conn) {
    string query = "UPDATE RENDEZVOUS SET temps = '" + temps + "', tarifs = '" + to_string(tarifs) +
    "', type_consultation = '" + typeConsultation + "', patient_id = '" +
    to_string(patientId) + "', docteur_id = '" + to_string(docteurId) +
    "' WHERE RENDEZVOUS_ID = " + to_string(id);
    conn.executeQuery(query);
}

void RendezVous::deleteRecord(OracleConnection& conn) {
    string query = "DELETE FROM RENDEZVOUS WHERE RENDEZVOUS_ID = " + to_string(id);
    conn.executeQuery(query);
}

// Getters and Setters
int RendezVous::getId()  { return id; }
void RendezVous::setId(int id) { this->id = id; }

string RendezVous::getTemps()  { return temps; }
void RendezVous::setTemps( string& temps) { this->temps = temps; }

double RendezVous::getTarifs()  { return tarifs; }
void RendezVous::setTarifs(double tarifs) { this->tarifs = tarifs; }

string RendezVous::getTypeConsultation()  { return typeConsultation; }
void RendezVous::setTypeConsultation( string& typeConsultation) { this->typeConsultation = typeConsultation; }

int RendezVous::getPatientId()  { return patientId; }
void RendezVous::setPatientId(int patientId) { this->patientId = patientId; }

int RendezVous::getDocteurId()  { return docteurId; }
void RendezVous::setDocteurId(int docteurId) { this->docteurId = docteurId; }
