import React, { useState, useEffect } from 'react';
import axios from 'axios';
import { useNavigate } from 'react-router-dom'; // Import useNavigate
import './Profilepage.css';
import { useUser } from "../UserContext";

const ProfilePage = () => {
  const [userInfo, setUserInfo] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const navigate = useNavigate(); // Initialize navigate
  const { user } = useUser();


  useEffect(() => {
    axios.get(`http://127.0.0.1:8080/user/${user.id}`)
      .then(response => {
        setUserInfo(response.data);
        setLoading(false);
      })
      .catch(err => {
        setError('Error fetching data');
        setLoading(false);
      });
  }, []);

  const handleLogoutClick = () => {
    navigate('/Signin'); // Navigate to the sign-in page
  };

  if (loading) {
    return <div>Loading...</div>;
  }

  if (error) {
    return <div>{error}</div>;
  }

  return (
    <div className="profile-page">
      <header className="header">
        <h1 className="app-title">DoConnect</h1>
         <button className="profile-button" onClick={handleLogoutClick}>
          Logout
        </button>
      </header>

      <main>
        <section className="profile-section">
          <h2 className="profile-title">Informations du Profil</h2>
          <div className="profile-info">
            <div className="profile-item">
              <strong>Nom:</strong> {userInfo.prenom} {userInfo.nom}
            </div>
            <div className="profile-item">
              <strong>Email:</strong> {userInfo.email}
            </div>
            <div className="profile-item">
              <strong>Adresse:</strong> {userInfo.adresse}
            </div>
            <div className="profile-item">
              <strong>Téléphone:</strong> {userInfo.telephone}
            </div>
            <div className="profile-item">
              <strong>Sexe:</strong> {userInfo.sexe}
            </div>
          </div>
        </section>
      </main>

      <footer className="footer">
        <p>DoConnect - Votre plateforme de santé en ligne</p>
        <p>Email : support@doconnect.com</p>
        <p>Téléphone : +212 600-000-000</p>
        <p>&copy; 2025 DoConnect. Tous droits réservés.</p>
      </footer>
    </div>
  );
};

export default ProfilePage;
