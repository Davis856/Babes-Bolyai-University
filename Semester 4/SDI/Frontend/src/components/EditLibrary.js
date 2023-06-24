import React, { useState, useEffect } from "react";
import { useNavigate, useParams } from "react-router-dom";
import axios from "axios";

function EditLibrary(props) {
  const [library, setLibrary] = useState({
    name: "",
    description: "",
    location: "",
    rating: "",
    owner: "",
  });
  const [errors, setErrors] = useState({});

  const navigate = useNavigate();
  const { id } = useParams();

  useEffect(() => {
    fetchLibrary();
  });

  const userString = localStorage.getItem("user");
  const user = JSON.parse(userString);

  const jwtToken = user.jwtToken;

  const fetchLibrary = () => {
    axios
      .get(`/api/libraries/${id}`)
      .then((response) => setLibrary(response.data))
      .catch((error) => {
        setErrors({ fetch: "Failed to fetch library." });
        console.log(error);
      });
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    axios
      .put(`/api/libraries/${id}`, library, {
        headers: {
          Authorization: jwtToken,
        },
      })
      .then((response) => {
        console.log(response);
        navigate("/libraries");
      })
      .catch((error) => {
        if (error.response) {
          setErrors(error.response.data);
        } else {
          setErrors({ submit: "Failed to update library." });
        }
        console.log(error);
      });
  };

  const handleInputChange = (event) => {
    const { name, value } = event.target;
    setLibrary((prevLibrary) => ({
      ...prevLibrary,
      [name]: value,
    }));
  };

  const role = props.roles;

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  return (
    <div className="container">
      <h1>Edit Library</h1>
      <form onSubmit={handleSubmit}>
        <div className="form-group">
          <label htmlFor="name">Name:</label>
          <input
            type="text"
            className="form-control"
            id="name"
            name="name"
            value={library.name}
            onChange={handleInputChange}
          />
          {errors.name && <div className="text-danger">{errors.name}</div>}
        </div>
        <div className="form-group">
          <label htmlFor="description">Description:</label>
          <textarea
            className="form-control"
            id="description"
            name="description"
            value={library.description}
            onChange={handleInputChange}
          ></textarea>
          {errors.description && (
            <div className="text-danger">{errors.description}</div>
          )}
        </div>
        <div className="form-group">
          <label htmlFor="location">Location:</label>
          <input
            type="location"
            className="form-control"
            id="location"
            name="location"
            value={library.location}
            onChange={handleInputChange}
          />
          {errors.location && (
            <div className="text-danger">{errors.location}</div>
          )}
        </div>
        <div className="form-group">
          <label htmlFor="rating">Rating:</label>
          <input
            type="number"
            className="form-control"
            id="rating"
            name="rating"
            value={library.rating}
            onChange={handleInputChange}
          />
          {errors.rating && <div className="text-danger">{errors.rating}</div>}
        </div>
        <div className="form-group">
          <label htmlFor="owner">Owner:</label>
          <input
            type="text"
            className="form-control"
            id="owner"
            name="owner"
            value={library.owner}
            onChange={handleInputChange}
          />
          {errors.owner && <div className="text-danger">{errors.owner}</div>}
        </div>
        {errors.fetch && <div className="text-danger">{errors.fetch}</div>}
        {errors.submit && <div className="text-danger">{errors.submit}</div>}
        <button type="submit" className="btn btn-primary">
          Update Library
        </button>
      </form>
    </div>
  );
}

export default EditLibrary;
