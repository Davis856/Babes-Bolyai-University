import React from "react";
import { Link } from "react-router-dom";

function Header(props) {
  const isAuthenticated = props.isAuthenticated;
  const roles = props.roles;
  const id = props.id;

  return (
    <ul className="navbar-nav mr-auto">
      <li className="nav-item">
        <Link className="nav-link" to="/">
          Home
        </Link>
      </li>
      <li className="nav-item">
        {!isAuthenticated && (
          <Link className="nav-link" to="/login">
            Login
          </Link>
        )}
      </li>
      <li className="nav-item">
        {!isAuthenticated && (
          <Link className="nav-link" to="/register">
            Register
          </Link>
        )}
      </li>
      <li className="nav-item">
        {isAuthenticated && roles && roles.includes("ROLE_ADMIN") && (
          <Link className="nav-link" to="/dashboard">
            Dashboard
          </Link>
        )}
      </li>
      <li className="nav-item">
        {isAuthenticated && (
          <Link className="nav-link" to={`/profile/${id}`}>
            Profile
          </Link>
        )}
      </li>
      <li className="nav-item">
        {isAuthenticated && (
          <Link className="nav-link" to="/logout">
            Logout
          </Link>
        )}
      </li>
    </ul>
  );
}

export default Header;
