import React, { useState, useEffect } from 'react';
import axios from 'axios';
import './DoctorDashboard.css'; // Assuming you have a CSS file for styling

const DoctorDashboard = () => {
  const [appointments, setAppointments] = useState([]);
  const [loading, setLoading] = useState(false);

  useEffect(() => {
    setLoading(true);
    // Assuming you have an endpoint that returns the appointments for a doctor
    axios.get('https://example.com/api/appointments')
      .then(response => {
        setAppointments(response.data); // Set the list of appointments
        setLoading(false);
      })
      .catch(error => {
        console.error('There was an error fetching the appointments!', error);
        setLoading(false);
      });
  }, []);

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
                  <th>Spécialité</th>
                  <th>Date</th>
                  <th>Heure</th>
                  <th>Statut</th>
                </tr>
              </thead>
              <tbody>
                {appointments.map((appointment, index) => (
                  <tr key={index}>
                    <td>{appointment.patientName}</td>
                    <td>{appointment.speciality}</td>
                    <td>{appointment.date}</td>
                    <td>{appointment.time}</td>
                    <td>{appointment.status}</td>
                  </tr>
                ))}
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
