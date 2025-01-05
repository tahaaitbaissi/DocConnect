import React, { useState } from 'react'; 
import axios from 'axios';
import './Signin.css'; 
import { Link,useNavigate } from 'react-router-dom'; // Assuming you have a CSS file for styling

const Signin = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(false);
  const navigate = useNavigate();

  const handleSubmit = (e) => {
    e.preventDefault();
    setLoading(true);
    setError(null);

    axios.post('http://127.0.0.1:8080/user/login',{ email, password }) // Adjust the API endpoint
      .then(response => {
        setLoading(false);
        // Handle the response, such as saving the token or user info
        console.log(response.data.role);
        if(response.data.role==="doctor"){
          navigate("/doctor-dashboard");
        }else{
          navigate("/patient");
        }

      })
      .catch(err => {
        setLoading(false);
        setError('Invalid email or password.');
      });
  };

  return (
    <div className="signin-page">
      <header className="header">
        <h1 className="app-title">DoConnect - Sign In</h1>
      </header>

      <main className='m'>
        <section className="signin-section">
          <h2 className="signin-title">Se connecter</h2>
          <form onSubmit={handleSubmit} className="signin-form">
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
              <label htmlFor="password">Mot de passe</label>
              <input
                type="password"
                id="password"
                value={password}
                onChange={(e) => setPassword(e.target.value)}
                required
              />
            </div>
            {error && <div className="error-message">{error}</div>}
            <button type="submit" className="signin-button" disabled={loading}>
              {loading ? 'Loading...' : 'Se connecter'}
            </button>
          </form>
        </section>
        {/* Link to Sign Up page */}
        <div className="signup-link">
            <p>Pas encore inscrit? <Link to="/signup">S'inscrire</Link></p>
          </div>
      </main>
    </div>
  );
};

export default Signin;
