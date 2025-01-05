import React from 'react'; 
import { useNavigate } from 'react-router-dom'; // استيراد useNavigate من React Router
import './patient.css';

const Patient = () => {
  const navigate = useNavigate(); // للحصول على دالة التوجيه

  const handleProfileClick = () => {
    navigate('/profile'); // التوجيه إلى صفحة الملف الشخصي
  };

  return (
    <div className="patient-page">
      {/* Header */}
      <header className="header">
        <h1 className="app-title">DoConnect</h1>
        <button className="profile-button" onClick={handleProfileClick}>
          Profile
        </button>
      </header>

      {/* Main Content */}
      <main>
        <section className="intro-section">
          <h2 className="intro-title">Consulter votre médecin facilement</h2>

          {/* Search Section */}
          <div className="search-section">
            <input
              type="text"
              placeholder="Rechercher une spécialité"
              className="search-bar"
            />
            <select className="city-select">
              <option value="">Sélectionnez une ville</option>
              <option value="Casablanca">Casablanca</option>
              <option value="Rabat">Rabat</option>
              <option value="Marrakech">Marrakech</option>
              <option value="Fès">Fès</option>
            </select>
            <button className="search-button">Rechercher</button>
          </div>
        </section>

        {/* Services and About Us Section */}
        <section className="info-sections">
          {/* Services Section */}
          <div className="services-section">
            <h2 className="services-title">Nos Services</h2>
            <ul className="services-list">
              <li>Consultation en ligne</li>
              <li>Rendez-vous rapide</li>
              <li>Accès aux meilleurs médecins</li>
              <li>Support 24/7</li>
            </ul>
          </div>

          {/* About Us Section */}
          <div className="about-section">
            <h2 className="about-title">À Propos de Nous</h2>
            <p className="about-text">
              DoConnect vous permet de trouver et de consulter des médecins en quelques clics. Notre plateforme vous offre un accès facile à des médecins de confiance, avec la possibilité de prendre rendez-vous rapidement et de consulter en ligne pour un confort maximal.
            </p>
            <button className="read-more-button">En savoir plus</button>
          </div>
        </section>
      </main>

      {/* Footer */}
      <footer className="footer">
        <div className="footer-info">
          <p>DoConnect - Votre plateforme de santé en ligne</p>
          <p>Email : support@doconnect.com</p>
          <p>Téléphone : +212 600-000-000</p>
          <div className="social-links">
            
           
          </div>
        </div>
        <div className="footer-bottom">
          <p>&copy; 2025 DoConnect. Tous droits réservés.</p>
        </div>
      </footer>
    </div>
  );
};

export default Patient;
