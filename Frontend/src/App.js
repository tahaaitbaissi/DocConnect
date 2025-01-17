import { BrowserRouter as Router, Routes, Route } from 'react-router-dom'; 
import Signup from './compoments/Signup';
import Signin from './compoments/Signin';
import Patient from './compoments/Patient';
import DoctorDashboard from './compoments/DoctorDashboard';
import ProfilePage from './compoments/Profilepage';
import { UserProvider } from "./UserContext";

function App() {
  return (
    <UserProvider>
    <Router>
      <Routes>
        <Route path="/Signin" element={<Signin />} />
        <Route path="/Signup" element={<Signup />} />
        <Route path="/patient" element={<Patient />} />
        <Route path="/doctor-dashboard" element={<DoctorDashboard />} />
        <Route path="/profile" element={<ProfilePage />} />
        <Route path="/" element={<Signup />} />
      </Routes>
    </Router>
    </UserProvider>
  );
}

export default App;
