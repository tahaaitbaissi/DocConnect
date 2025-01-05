import React, { createContext, useState, useContext, useEffect } from "react";

// Créer le contexte utilisateur
const UserContext = createContext();

// Provider pour fournir les données utilisateur
export const UserProvider = ({ children }) => {
  const [user, setUser] = useState(null);

  // Charger l'utilisateur depuis localStorage au montage
  useEffect(() => {
    const storedUser = localStorage.getItem("user");
    if (storedUser) {
      setUser(JSON.parse(storedUser)); // Convertir la chaîne JSON en objet
    }
  }, []);

  // Mettre à jour localStorage chaque fois que l'utilisateur change
  useEffect(() => {
    if (user) {
      localStorage.setItem("user", JSON.stringify(user)); // Sauvegarder les données
    } else {
      localStorage.removeItem("user"); // Supprimer si déconnecté
    }
  }, [user]);

  // Fonction pour se déconnecter
  const logout = () => {
    setUser(null); // Réinitialiser l'utilisateur
    localStorage.removeItem("user"); // Supprimer les données utilisateur du localStorage
  };

  return (
    <UserContext.Provider value={{ user, setUser, logout }}>
      {children}
    </UserContext.Provider>
  );
};

// Hook personnalisé pour consommer le contexte
export const useUser = () => {
  return useContext(UserContext);
};
