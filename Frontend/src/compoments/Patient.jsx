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
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [selectedDoctor, setSelectedDoctor] = useState(null);
  const [appointmentTime, setAppointmentTime] = useState('');
  const [consultationType, setConsultationType] = useState('');
  const [price, setPrice] = useState('');

  // Fetch cities and categories from the backend
  useEffect(() => {
    axios.get('http://127.0.0.1:8080/admin/villes')
      .then(response => setCities(response.data))
      .catch(error => console.error('Error fetching cities:', error));

    axios.get('http://127.0.0.1:8080/admin/categories')
      .then(response => setCategories(response.data))
      .catch(error => console.error('Error fetching categories:', error));
  }, []);

  const handleProfileClick = () => {
    navigate('/profile');
  };

  const handleSearch = async () => {
    setLoading(true);

    try {
      let response;

      if (searchQuery) {
        response = await axios.get(`http://127.0.0.1:8080/search/doctors/${searchQuery}`);
      } else if (selectedCategory) {
        response = await axios.get(`http://127.0.0.1:8080/search/doctors/category/${selectedCategory}`);
      } else if (selectedCity) {
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

  const openBookingModal = (doctor) => {
    setSelectedDoctor(doctor);
    setIsModalOpen(true);
  };

  const closeBookingModal = () => {
    setIsModalOpen(false);
  };

  const handleConfirmAppointment = () => {
    console.log({
      doctor: selectedDoctor,
      appointmentTime,
      consultationType,
      price,
    });
  };

  return (
    <div className="patient-page">
      {/* Header */}
      <header className="header">
        <h1 className="app-title">DoConnect</h1>
        <button className="profile-button" onClick={handleProfileClick}>Profile</button>
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

            <button className="search-button" onClick={handleSearch}>Rechercher</button>
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
                    <button onClick={() => openBookingModal(doctor)}>Reserver un rendez-vous</button>
                  </li>
                ))
              ) : (
                <p>Aucun médecin trouvé</p>
              )}
            </ul>
          )}
        </section>
      </main>

      {/* Modal for Booking Appointment */}
      {isModalOpen && (
        <div className="modal">
          <div className="modal-content">
            <h2>Réserver un rendez-vous avec Dr. {selectedDoctor.nom}</h2>
            <label>Choisir l'heure :</label>
            <input
              type="datetime-local"
              value={appointmentTime}
              onChange={(e) => setAppointmentTime(e.target.value)}
            />

            <label>Type de consultation :</label>
            <select
              value={consultationType}
              onChange={(e) => setConsultationType(e.target.value)}
            >
              <option value="video">Appel vidéo</option>
              <option value="cabinet">Cabinet</option>
            </select>

            <label>Prix :</label>
            <input
              type="number"
              value={price}
              onChange={(e) => setPrice(e.target.value)}
              placeholder="Prix de la consultation"
            />

            <button onClick={handleConfirmAppointment}>Confirmer</button>
            <button onClick={closeBookingModal}>Annuler</button>
          </div>
        </div>
      )}

      {/* Footer */}
      <footer className="footer">
        <p>DoConnect - Votre plateforme de santé en ligne</p>
        <p>Email : support@doconnect.com</p>
        <p>Téléphone : +212 600-000-000</p>
        <p>&copy; 2025 DoConnect. Tous droits réservés.</p>
      </footer>
    </div>
  );
};

export default Patient;
