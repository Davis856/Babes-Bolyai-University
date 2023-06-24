import React, { useState, useEffect } from "react";
import { useNavigate, useParams } from "react-router-dom";
import axios from "axios";

function EditAuthor(props) {
  const [author, setAuthor] = useState({
    name: "",
    email: "",
    bio: "",
    country: "",
  });

  const [errors, setErrors] = useState({
    name: "",
    email: "",
    bio: "",
    country: "",
  });

  const navigate = useNavigate();
  const { id } = useParams();

  useEffect(() => {
    fetchAuthor();
  });

  const role = props.roles;

  const userString = localStorage.getItem("user");
  const user = JSON.parse(userString);

  const jwtToken = user.jwtToken;

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  const fetchAuthor = () => {
    axios
      .get(`/api/authors/${id}`)
      .then((response) => setAuthor(response.data))
      .catch((error) => console.log(error));
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    const validationErrors = validateForm(author);
    if (Object.keys(validationErrors).length === 0) {
      axios
        .put(`/api/authors/${id}`, author, {
          headers: {
            Authorization: jwtToken,
          },
        })
        .then((response) => {
          console.log(response);
          navigate("/authors");
        })
        .catch((error) => console.log(error));
    } else {
      setErrors(validationErrors);
    }
  };

  const handleInputChange = (event) => {
    const { name, value } = event.target;
    setAuthor((prevAuthor) => ({
      ...prevAuthor,
      [name]: value,
    }));
  };

  const validateForm = (author) => {
    const errors = {};
    if (!author.name.trim()) {
      errors.name = "Name is required";
    }
    if (!author.email.trim()) {
      errors.email = "Email is required";
    } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(author.email)) {
      errors.email = "Invalid email format";
    }
    if (!author.bio.trim()) {
      errors.bio = "Bio is required";
    }
    if (!author.country.trim()) {
      errors.country = "Country is required";
    }
    return errors;
  };

  return (
    <div className="container">
      <h1>Edit Author</h1>
      <form onSubmit={handleSubmit}>
        <div className="form-group">
          <label htmlFor="name">Name:</label>
          <input
            type="text"
            className="form-control"
            id="name"
            name="name"
            value={author.name}
            onChange={handleInputChange}
          />
          {errors.name && (
            <div className="alert alert-danger">{errors.name}</div>
          )}
        </div>
        <div className="form-group">
          <label htmlFor="email">Email:</label>
          <input
            type="email"
            className="form-control"
            id="email"
            name="email"
            value={author.email}
            onChange={handleInputChange}
          />
          {errors.email && (
            <div className="alert alert-danger">{errors.email}</div>
          )}
        </div>
        <div className="mb-3">
          <label className="form-label" htmlFor="bio">
            Bio:
          </label>
          <textarea
            className="form-control"
            id="bio"
            name="bio"
            value={author.bio}
            onChange={handleInputChange}
          />
          {errors.bio && <div className="alert alert-danger">{errors.bio}</div>}
        </div>
        <div className="mb-3">
          <label className="form-label" htmlFor="country">
            Country:
          </label>
          <input
            type="text"
            className="form-control"
            id="country"
            name="country"
            value={author.country}
            onChange={handleInputChange}
          />
          {errors.country && (
            <div className="alert alert-danger">{errors.country}</div>
          )}
        </div>
        <button type="submit" className="btn btn-primary">
          Create
        </button>
      </form>
    </div>
  );
}

export default EditAuthor;
