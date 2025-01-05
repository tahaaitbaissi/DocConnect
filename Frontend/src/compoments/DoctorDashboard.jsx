import React, { useState, useEffect } from 'react';
import axios from 'axios';
import './DoctorDashboard.css'; // Assuming you have a CSS file for styling
import { useUser } from "../UserContext";

const DoctorDashboard = () => {
  const [appointments, setAppointments] = useState([]);
  const [patientDetails, setPatientDetails] = useState({});
  const [loading, setLoading] = useState(false);
  const { user } = useUser();

  useEffect(() => {
    setLoading(true);

    // Fetch appointments for the doctor
    axios.get(`http://127.0.0.1:8080/rendezvous/doctor/${user.id}`)
    .then(response => {
      const fetchedAppointments = response.data;
      setAppointments(fetchedAppointments);

      // Fetch patient details for each appointment
      const patientPromises = fetchedAppointments.map(appointment => {
        const { patient_id } = appointment;

        // If patient details are already cached, skip the API call
        if (patientDetails[patient_id]) {
          return Promise.resolve({ id: patient_id, ...patientDetails[patient_id] });
        }

        // Otherwise, fetch patient details from the server
        return axios.get(`http://127.0.0.1:8080/user/${patient_id}`)
        .then(patientResponse => {
          const patient = patientResponse.data;
          setPatientDetails(prev => ({ ...prev, [patient_id]: patient }));
          return { id: patient_id, ...patient };
        })
        .catch(err => {
          console.error(`Failed to fetch details for patient ID ${patient_id}`, err);
          return { id: patient_id, name: "Unknown" }; // Fallback for missing data
        });
      });

      // Wait for all patient detail fetches to complete
      Promise.all(patientPromises).then(() => setLoading(false));
    })
    .catch(error => {
      console.error('Error fetching appointments:', error);
      setLoading(false);
    });
  }, [user.id]);

  // Function to format the date and time string separately
  const formatDate = (dateString) => {
    const [datePart, timePart, period] = dateString.split(' ');

    const [day, month, year] = datePart.split('-');
    const monthNames = {
      'JAN': '01', 'FEB': '02', 'MAR': '03', 'APR': '04',
      'MAY': '05', 'JUN': '06', 'JUL': '07', 'AUG': '08',
      'SEP': '09', 'OCT': '10', 'NOV': '11', 'DEC': '12'
    };
    const formattedMonth = monthNames[month];
    const formattedDate = `${year}-${formattedMonth}-${day}`;

    const [hour, minute, second] = timePart.split('.');
    let hour24 = parseInt(hour);
    if (period === 'PM' && hour24 !== 12) {
      hour24 += 12;
    } else if (period === 'AM' && hour24 === 12) {
      hour24 = 0;
    }
    const formattedTime = `${hour24.toString().padStart(2, '0')}:${minute}:${second}`;

    return { date: formattedDate, time: formattedTime };
  };

  return (
    <div className="doctor-dashboard">
    <header className="header">
    <h1 className="app-title">Tableau de Bord du Docteur</h1>
    </header>

    <main>
    <section className="appointments-section">
    <h2 className="appointments-title">Rendez-vous à venir</h2>
    {loading ? (
      <p>Chargement des rendez-vous...</p>
    ) : (
      <table className="appointments-table">
      <thead>
      <tr>
      <th>Nom du patient</th>
      <th>Type De Consultation</th>
      <th>Date</th>
      <th>Heure</th>
      <th>Tarif</th>
      </tr>
      </thead>
      <tbody>
      {appointments.map((appointment, index) => {
        const { date, time } = formatDate(appointment.temps);
        const patient = patientDetails[appointment.patient_id];
        const patientName = patient ? `${patient.nom} ${patient.prenom}` : "Chargement...";

        return (
          <tr key={index}>
          <td className="Rc">{patientName}</td>
          <td className="Rc">{appointment.type_consultation}</td>
          <td className="Rc">{date}</td>
          <td className="Rc">{time}</td>
          <td className="Rc">{appointment.tarifs} €</td>
          </tr>
        );
      })}
      </tbody>
      </table>
    )}
    </section>
    </main>

    <footer className="footer">
    <div className="footer-info">
    <p>DoConnect - Votre plateforme de santé en ligne</p>
    </div>
    <div className="footer-bottom">
    <p>&copy; 2025 DoConnect. Tous droits réservés.</p>
    </div>
    </footer>
    </div>
  );
};

export default DoctorDashboard;
