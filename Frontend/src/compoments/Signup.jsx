import React, { useState } from 'react';
import axios from 'axios';
import { useNavigate } from 'react-router-dom';
import './Signup.css'; // Assuming you have a CSS file for styling

const Signup = () => {
  const [firstName, setFirstName] = useState('');
  const [lastName, setLastName] = useState('');
  const [email, setEmail] = useState('');
  const [address, setAddress] = useState('');
  const [phone, setPhone] = useState('');
  const [gender, setGender] = useState('');
  const [role, setRole] = useState('patient'); // Default role is 'patient'
  const [password, setPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(false);

  const navigate = useNavigate();

  const handleSubmit = (e) => {
    e.preventDefault();
    if (password !== confirmPassword) {
      setError('Les mots de passe ne correspondent pas.');
      return;
    }
    setLoading(true);
    setError(null);

    axios.post('http://localhost:8080/user/register', {
      firstName, lastName, email, address, phone, gender, role, password
    })
      .then(response => {
        setLoading(false);
        // Redirect to Patient page if the role is 'patient'
        if (role === 'Patient') {
          navigate('/Patient'); // Redirect to patient page
        } else {
          navigate('/Doctor-dashboard'); // Redirect to doctor dashboard
        }
      })
      .catch(err => {
        setLoading(false);
        setError('Quelque chose a mal tourné. Veuillez réessayer.');
      });
  };

  return (
    <div className="signup-page">
      <header className="header">
        <h1 className="app-title">DoConnect - S'inscrire</h1>
      </header>

      <main>
        <section className="signup-section">
          <h2 className="signup-title">S'inscrire</h2>
          <form onSubmit={handleSubmit} className="signup-form">
            <div className="form-item">
              <label htmlFor="firstName">Nom</label>
              <input
                type="text"
                id="firstName"
                value={firstName}
                onChange={(e) => setFirstName(e.target.value)}
                required
              />
            </div>
            <div className="form-item">
              <label htmlFor="lastName">Prénom</label>
              <input
                type="text"
                id="lastName"
                value={lastName}
                onChange={(e) => setLastName(e.target.value)}
                required
              />
            </div>
            <div className="form-item">
              <label htmlFor="email">Email</label>
              <input
                type="email"
                id="email"
                value={email}
                onChange={(e) => setEmail(e.target.value)}
                required
              />
            </div>
            <div className="form-item">
              <label htmlFor="address">Adresse</label>
              <input
                type="text"
                id="address"
                value={address}
                onChange={(e) => setAddress(e.target.value)}
                required
              />
            </div>
            <div className="form-item">
              <label htmlFor="phone">Téléphone</label>
              <input
                type="text"
                id="phone"
                value={phone}
                onChange={(e) => setPhone(e.target.value)}
                required
              />
            </div>
            <div className="form-item">
              <label htmlFor="gender">Sexe</label>
              <select
                id="gender"
                value={gender}
                onChange={(e) => setGender(e.target.value)}
                required
              >
                <option value="">Sélectionnez</option>
                <option value="male">Homme</option>
                <option value="female">Femme</option>
              </select>
            </div>
            <div className="form-item">
              <label htmlFor="role">Je suis un</label>
              <select
                id="role"
                value={role}
                onChange={(e) => setRole(e.target.value)}
                required
              >
                <option value="patient">Patient</option>
                <option value="doctor">Docteur</option>
              </select>
            </div>
            <div className="form-item">
              <label htmlFor="password">Mot de passe</label>
              <input
                type="password"
                id="password"
                value={password}
                onChange={(e) => setPassword(e.target.value)}
                required
              />
            </div>
            <div className="form-item">
              <label htmlFor="confirmPassword">Confirmer le mot de passe</label>
              <input
                type="password"
                id="confirmPassword"
                value={confirmPassword}
                onChange={(e) => setConfirmPassword(e.target.value)}
                required
              />
            </div>
            {error && <div className="error-message">{error}</div>}
            <button type="submit" className="signup-button" disabled={loading}>
              {loading ? 'Chargement...' : "S'inscrire"}
            </button>
          </form>
        </section>
      </main>
    </div>
  );
};

export default Signup;
