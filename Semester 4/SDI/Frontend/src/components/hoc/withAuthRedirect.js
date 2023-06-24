import React from "react";
import { Navigate } from "react-router-dom";

const withAuthRedirect = (Component) => {
  const AuthRedirect = (props) => {
    const isAuthenticated = localStorage.getItem("user") !== null;
    if (isAuthenticated) {
      return <Navigate to="/" />;
    }
    return <Component {...props} />;
  };
  return AuthRedirect;
};

export default withAuthRedirect;
