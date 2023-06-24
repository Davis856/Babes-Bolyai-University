import React, { useState, useContext } from "react";
import AuthService from "../../services/AuthService";

function Login(props) {
  const isAuthenticated = props.isAuthenticated;

  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [loading, setLoading] = useState(false);
  const [message, setMessage] = useState("");
  const [errorMessage, setErrorMessage] = useState("");

  if (isAuthenticated) {
    window.location.href = "/";
    return null;
  }

  const handleLogin = async (e) => {
    e.preventDefault();

    setMessage("");
    setLoading(true);

    try {
      await AuthService.login({ username, password });
      setLoading(false);
      setMessage("Login successful. Redirecting...");
      setTimeout(() => {
        window.location.href = "/";
      }, 3000);
    } catch (error) {
      const resMessage =
        (error.response &&
          error.response.data &&
          error.response.data.message) ||
        error.message ||
        error.toString();

      setLoading(false);
      setErrorMessage(resMessage);
    }
  };

  return (
    <div>
      <form onSubmit={handleLogin}>
        {errorMessage && (
          <div className="alert alert-danger">{errorMessage}</div>
        )}
        <h3>Login</h3>

        <div className="form-group">
          <label htmlFor="username">Username</label>
          <input
            type="text"
            className="form-control"
            id="username"
            required
            value={username}
            onChange={(e) => setUsername(e.target.value)}
            name="username"
          />
        </div>

        <div className="form-group">
          <label htmlFor="password">Password</label>
          <input
            type="password"
            className="form-control"
            id="password"
            required
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            name="password"
          />
        </div>

        <div className="form-group">
          <button className="btn btn-primary btn-block" disabled={loading}>
            {loading && (
              <span className="spinner-border spinner-border-sm"></span>
            )}
            <span>Login</span>
          </button>
        </div>

        {message && (
          <div className="form-group">
            <div className="alert alert-success" role="alert">
              {message}
            </div>
          </div>
        )}
      </form>
    </div>
  );
}

export default Login;
