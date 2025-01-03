#include <iostream>
#include "app/models/OracleConnection.h"
#include "app/models/User.h"
#include "app/models/Doctor.h"
#include "app/models/Patient.h"
#include "app/models/Soins.h"
#include "app/models/Categorie.h"
#include "app/models/Ville.h"

using namespace std;

int main() {
    OracleConnection conn;  // Establish connection to the database
    conn.connect();

    // --- 1. Create a New User (Doctor or Patient) ---
    cout << "Creating new Doctor..." << endl;
    Doctor doctor;
    doctor.setNom("Ait Baissi");
    doctor.setPrenom("Taha");
    doctor.setEmail("tahaaitbaissi@gmail.com");
    doctor.setPassword("password");
    doctor.setAdresse("adresse");
    doctor.setTelephone("0606060606");
    doctor.setWorkHours("9:00 AM - 5:00 PM");
    doctor.setDescription("Experienced cardiologist");
    doctor.setConsultationType("cabinet");
    doctor.setCategorieId(1);  // Example category ID
    doctor.setVilleId(1);      // Example city ID
    doctor.create(conn);  // This will create both the user and the doctor

    cout << "Doctor created with ID: " << doctor.getId() << endl;

    // --- 2. Create a New Patient ---
    cout << "Creating new Patient..." << endl;
    Patient patient;
    patient.setNom("Amr");
    patient.setPrenom("Ahmed");
    patient.setEmail("ahmedamr@gmail.com");
    patient.setPassword("password");
    patient.setAdresse("adresse");
    patient.setTelephone("0606060606");
    patient.setDateOfBirth("1990-06-15");
    patient.create(conn);  // This will create both the user and the patient

    cout << "Patient created with ID: " << patient.getId() << endl;

    // --- 3. Create a New Soins (Treatment) ---
    cout << "Creating new Soins..." << endl;
    Soins soins;
    soins.setLibelle("Cardiac Consultation");
    soins.create(conn);  // This will insert the soins into the table

    cout << "Soins created with ID: " << soins.getId() << endl;

    // --- 4. Read Data (e.g., Doctor, Patient, Soins) ---
    cout << "\nReading Doctor's Data..." << endl;
    Doctor readDoctor;
    if (readDoctor.read(conn, doctor.getId())) {
        cout << "Doctor ID: " << readDoctor.getId() << ", Work Hours: " << readDoctor.getWorkHours() << endl;
    } else {
        cout << "Doctor not found!" << endl;
    }

    cout << "\nReading Patient's Data..." << endl;
    Patient readPatient;
    if (readPatient.read(conn, patient.getId())) {
        cout << "Patient ID: " << readPatient.getId() << ", Date of Birth: " << readPatient.getDateOfBirth() << endl;
    } else {
        cout << "Patient not found!" << endl;
    }

    cout << "\nReading Soins Data..." << endl;
    Soins readSoins;
    if (readSoins.read(conn, soins.getId())) {
        cout << "Soins ID: " << readSoins.getId() << ", Libelle: " << readSoins.getLibelle() << endl;
    } else {
        cout << "Soins not found!" << endl;
    }

    // --- 5. Update Data (e.g., Update Doctor's Information) ---
    cout << "\nUpdating Doctor's Work Hours..." << endl;
    doctor.setWorkHours("8:00 AM - 4:00 PM");
    doctor.update(conn);  // This will update both the user and the doctor in the database

    // Read again to verify update
    if (readDoctor.read(conn, doctor.getId())) {
        cout << "Updated Doctor's Work Hours: " << readDoctor.getWorkHours() << endl;
    }

    // --- 6. Delete Data (e.g., Delete a Soins entry) ---
    cout << "\nDeleting Soins..." << endl;
    soins.deleteRecord(conn);  // This will delete the soins from the table

    // Verify deletion
    if (!readSoins.read(conn, soins.getId())) {
        cout << "Soins entry deleted successfully!" << endl;
    } else {
        cout << "Soins deletion failed!" << endl;
    }

    // --- 7. Delete a Patient ---
    cout << "\nDeleting Patient..." << endl;
    patient.deleteRecord(conn);  // This will delete the patient

    // Verify deletion
    if (!readPatient.read(conn, patient.getId())) {
        cout << "Patient deleted successfully!" << endl;
    } else {
        cout << "Patient deletion failed!" << endl;
    }

    // --- End of Example ---
    return 0;
}
