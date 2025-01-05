import React, { useState, useEffect } from 'react';
import axios from 'axios';
import { useNavigate } from 'react-router-dom';
import './patient.css';

const Patient = () => {
  const navigate = useNavigate();
  const [cities, setCities] = useState([]);
  const [categories, setCategories] = useState([]);
  const [searchResults, setSearchResults] = useState([]);
  const [loading, setLoading] = useState(false);
  const [searchQuery, setSearchQuery] = useState('');
  const [selectedCity, setSelectedCity] = useState('');
  const [selectedCategory, setSelectedCategory] = useState('');

  // Fetch cities and categories from the backend when the component is mounted
  useEffect(() => {
    // Fetch cities
    axios.get('http://127.0.0.1:8080/admin/villes')
    .then((response) => {
      setCities(response.data);
    })
    .catch((error) => {
      console.error('Error fetching cities:', error);
    });

    // Fetch categories
    axios.get('http://127.0.0.1:8080/admin/categories')
    .then((response) => {
      setCategories(response.data);
    })
    .catch((error) => {
      console.error('Error fetching categories:', error);
    });
  }, []);

  const handleProfileClick = () => {
    navigate('/profile');
  };

  const handleSearch = async () => {
    setLoading(true);

    try {
      let response;

      if (searchQuery) {
        // Search for doctors by name
        response = await axios.get(`http://127.0.0.1:8080/search/doctors/${searchQuery}`);
      } else if (selectedCategory) {
        // Search for doctors by category ID
        response = await axios.get(`http://127.0.0.1:8080/search/doctors/category/${selectedCategory}`);
      } else if (selectedCity) {
        // Search for doctors by city ID
        response = await axios.get(`http://127.0.0.1:8080/search/doctors/city/${selectedCity}`);
      }

      if (response && response.data) {
        setSearchResults(response.data);
      }
    } catch (error) {
      console.error('Error searching doctors:', error);
    } finally {
      setLoading(false);
    }
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
    value={searchQuery}
    onChange={(e) => setSearchQuery(e.target.value)}
    />

    <select
    className="city-select"
    value={selectedCity}
    onChange={(e) => setSelectedCity(e.target.value)}
    >
    <option value="">Sélectionnez une ville</option>
    {cities.map((city) => (
      <option key={city.id} value={city.id}>
      {city.nom}
      </option>
    ))}
    </select>

    <select
    className="category-select"
    value={selectedCategory}
    onChange={(e) => setSelectedCategory(e.target.value)}
    >
    <option value="">Sélectionnez une catégorie</option>
    {categories.map((category) => (
      <option key={category.id} value={category.id}>
      {category.libelle}
      </option>
    ))}
    </select>

    <button className="search-button" onClick={handleSearch}>
    Rechercher
    </button>
    </div>
    </section>

    {/* Search Results */}
    <section className="search-results-section">
    {loading ? (
      <p>Chargement des résultats...</p>
    ) : (
      <ul className="search-results-list">
      {searchResults.length > 0 ? (
        searchResults.map((doctor, index) => (
          <li key={index}>
          <h3>{doctor.nom} {doctor.prenom}</h3>
          <p>Email: {doctor.email}</p>
          <p>Adresse: {doctor.adresse}</p>
          <p>Téléphone: {doctor.telephone}</p>
          <p>Speciality: {doctor.description}</p>
          </li>
        ))
      ) : (
        <p>Aucun médecin trouvé</p>
      )}
      </ul>
    )}
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
    </div>
    <div className="footer-bottom">
    <p>&copy; 2025 DoConnect. Tous droits réservés.</p>
    </div>
    </footer>
    </div>
  );
};

export default Patient;
