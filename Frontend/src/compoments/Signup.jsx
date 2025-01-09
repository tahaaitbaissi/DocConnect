import React, { useState, useEffect } from 'react';
import axios from 'axios';
import { useNavigate } from 'react-router-dom';
import { Link } from 'react-router-dom';  // Import Link
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

  // New state variables for doctor-specific fields
  const [birthDate, setBirthDate] = useState('');
  const [workHours, setWorkHours] = useState('');
  const [description, setDescription] = useState('');
  const [consultationType, setConsultationType] = useState('');

  const [villes, setVilles] = useState([]);
  const [categories, setCategories] = useState([]);
  const [soins, setSoins] = useState([]);

  const [selectedCategory, setSelectedCategory] = useState('');
  const [selectedVille, setSelectedVille] = useState('');

  const navigate = useNavigate();

  // Fetch villes and categories when the component mounts
  useEffect(() => {
    // Fetch villes
    axios.get('http://localhost:8080/admin/villes')
    .then(response => {
      setVilles(response.data);
    })
    .catch(error => console.log(error));

    // Fetch categories
    axios.get('http://localhost:8080/admin/categories')
    .then(response => {
      setCategories(response.data);
    })
    .catch(error => console.log(error));
  }, []);

  // Fetch soins when a category is selected
  useEffect(() => {
    if (selectedCategory) {
      axios.get(`http://localhost:8080/admin/soins/${selectedCategory}`)
      .then(response => {
        setSoins(response.data);
      })
      .catch(error => console.log(error));
    }
  }, [selectedCategory]);

  const handleSubmit = (e) => {
    e.preventDefault();
    if (password !== confirmPassword) {
      setError('Les mots de passe ne correspondent pas.');
      return;
    }
    setLoading(true);
    setError(null);

    const userData = {
      firstName, lastName, email, address, phone, gender, role, password
    };

    // Add doctor-specific fields if the role is doctor
    if (role === 'doctor') {
      userData.workHours = workHours;
      userData.description = description;
      userData.consultationType = consultationType;
      userData.ville = selectedVille;
      userData.category = selectedCategory;
      userData.soins = soins; // Pass selected soins to backend
    } else {
      userData.birthDate = birthDate;
    }

    axios.post('http://localhost:8080/user/register', userData)
    .then(response => {
      setLoading(false);
      // Redirect to Patient page if the role is 'patient'
      if (role === 'patient') {
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
    {/* Form fields */}
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
    <label htmlFor="Password<">Password</label>
    <input
    type="password"
    id="password"
    value={password}
    onChange={(e) => setPassword(e.target.value)}
    required
    />
    </div>
    <div className="form-item">
    <label htmlFor="ComfirmPassword">Confirm Password</label>
    <input
    type="password"
    id="confirmPassword"
    value={confirmPassword}
    onChange={(e) => setConfirmPassword(e.target.value)}
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

    {/* Additional fields for doctor */}
    {role === 'doctor' && (
      <>
      <div className="form-item">
      <label htmlFor="workHours">Heures de travail</label>
      <input
      type="text"
      id="workHours"
      value={workHours}
      onChange={(e) => setWorkHours(e.target.value)}
      required
      />
      </div>
      <div className="form-item">
      <label htmlFor="description">Description</label>
      <input
      type="text"
      id="description"
      value={description}
      onChange={(e) => setDescription(e.target.value)}
      required
      />
      </div>
      <div className="form-item">
      <label htmlFor="consultationType">Type de consultation</label>
      <select
      id="consultationType"
      value={consultationType}
      onChange={(e) => setConsultationType(e.target.value)}
      required
      >
      <option value="">Sélectionnez</option>
      <option value="domicile">Domicile</option>
      <option value="cabinet">Cabinet</option>
      <option value="video">Vidéo</option>
      </select>
      </div>
      <div className="form-item">
      <label htmlFor="ville">Ville</label>
      <select
      id="ville"
      value={selectedVille}
      onChange={(e) => setSelectedVille(e.target.value)}
      required
      >
      <option value="">Sélectionnez une ville</option>
      {villes.map(ville => (
        <option key={ville.id} value={ville.id}>{ville.nom}</option>
      ))}
      </select>
      </div>
      <div className="form-item">
      <label htmlFor="category">Catégorie</label>
      <select
      id="category"
      value={selectedCategory}
      onChange={(e) => setSelectedCategory(e.target.value)}
      required
      >
      <option value="">Sélectionnez une catégorie</option>
      {categories.map(category => (
        <option key={category.id} value={category.id}>{category.libelle}</option>
      ))}
      </select>
      </div>
      {selectedCategory && (
        <div className="form-item">
        <label htmlFor="soins">Soins</label>
        <select
        id="soins"
        required
        >
        <option value="">Sélectionnez un soin</option>
        {soins.map(soin => (
          <option key={soin.id} value={soin.id}>{soin.libelle}</option>
        ))}
        </select>
        </div>
      )}
      </>
    )}

    {/* Patient-specific field */}
    {role === 'patient' && (
      <div className="form-item">
      <label htmlFor="birthDate">Date de naissance</label>
      <input
      type="date"
      id="birthDate"
      value={birthDate}
      onChange={(e) => setBirthDate(e.target.value)}
      required
      />
      </div>
    )}

    {error && <div className="error-message">{error}</div>}
    <button type="submit" className="signup-button" disabled={loading}>
    {loading ? 'Chargement...' : "S'inscrire"}
    </button>
    </form>

    {/* Login link */}
    <div className="login-link">
    <p>Tu as un compte ? <Link to="/Signin">SE CONNECTER</Link></p>
    </div>
    </section>
    </main>
    </div>
  );
};

export default Signup;
