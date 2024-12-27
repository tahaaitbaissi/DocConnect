#ifndef RENDEZVOUSCONTROLLER_H_
#define RENDEZVOUSCONTROLLER_H_

#include <vector>
#include <string>
#include "../models/RendezVous.h"
#include "../models/OracleConnection.h"
#include "../models/Patient.h"
#include "../models/Doctor.h"

using namespace std;

class RendezVousController {
public:
    RendezVousController();
    ~RendezVousController();

    // CRUD Methods
    bool createAppointment(OracleConnection& conn, int doctorId, int patientId, string date, string time, double tariff, string consultationType);
    bool updateAppointment(OracleConnection& conn, int appointmentId, string newDate, string newTime, double newTariff);
    bool cancelAppointment(OracleConnection& conn, int appointmentId);

    // Business Logic Methods
    vector<RendezVous> getAppointmentsForPatient(OracleConnection& conn, int patientId);
    vector<RendezVous> getAppointmentsForDoctor(OracleConnection& conn, int doctorId);
    RendezVous getAppointmentDetails(OracleConnection& conn, int appointmentId);

    // Specific Features
    bool checkForConflictingAppointments(OracleConnection& conn, int doctorId, string date, string time);
    vector<RendezVous> getAppointmentsByConsultationType(OracleConnection& conn, string consultationType);
};

#endif // RENDEZVOUSCONTROLLER_H_
