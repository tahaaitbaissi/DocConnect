import React, { useState, useEffect } from 'react';
import axios from 'axios';
import { useNavigate } from 'react-router-dom'; // Import useNavigate
import './Profilepage.css';

const ProfilePage = () => {
  const [userInfo, setUserInfo] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const navigate = useNavigate(); // Initialize navigate

  useEffect(() => {
    axios.get('https://example.com/api/user') 
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
          Profile
        </button>
      </header>

      <main>
        <section className="profile-section">
          <h2 className="profile-title">Informations du Profil</h2>
          <div className="profile-info">
            <div className="profile-item">
              <strong>Nom:</strong> {userInfo.firstName} {userInfo.lastName}
            </div>
            <div className="profile-item">
              <strong>Email:</strong> {userInfo.email}
            </div>
            <div className="profile-item">
              <strong>Adresse:</strong> {userInfo.address}
            </div>
            <div className="profile-item">
              <strong>Téléphone:</strong> {userInfo.phone}
            </div>
            <div className="profile-item">
              <strong>Sexe:</strong> {userInfo.gender}
            </div>
            <div className="profile-item">
              <strong>Formation:</strong> {userInfo.education}
            </div>
          </div>
          <button className="update-button">Mettre à jour</button>
        </section>
      </main>

      <footer className="footer">
        <p>Contactez-nous :</p>
        <p>Email : support@doconnect.com</p>
        <p>Téléphone : +212 600-000-000</p>
      </footer>
    </div>
  );
};

export default ProfilePage;
