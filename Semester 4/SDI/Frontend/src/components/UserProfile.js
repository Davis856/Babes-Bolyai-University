import React, { useState, useEffect } from "react";
import { useNavigate, useParams } from "react-router-dom";
import axios from "axios";

function UserProfile(props) {
  const [user, setUser] = useState({
    id: "",
    bio: "",
    location: "",
    birthdate: "",
    gender: "",
    maritalStatus: "",
  });

  const [updatedUser, setUpdatedUser] = useState({ ...user });

  const [userStats, setUserStats] = useState({
    numberOfAuthors: 0,
    numberOfBooks: 0,
    numberOfLibraries: 0,
    numberOfLibraryBooks: 0,
  });

  const [errors, setErrors] = useState({
    id: "",
    bio: "",
    location: "",
    birthdate: "",
    gender: "",
    maritalStatus: "",
  });

  const [isLoading, setIsLoading] = useState(false);

  const navigate = useNavigate();
  const { id } = useParams();

  useEffect(() => {
    const fetchUser = () => {
      setIsLoading(true);
      axios
        .get(`/api/user-profile-id/${id}`)
        .then((response) => {
          setUser(response.data);
          setUpdatedUser(response.data);
          setIsLoading(false);
        })
        .catch((error) => {
          console.log(error);
          setIsLoading(false);
        });
    };

    const fetchUserStats = () => {
      setIsLoading(true);
      Promise.all([
        axios.get(`/api/user-number-authors/${id}`),
        axios.get(`/api/user-number-books/${id}`),
        axios.get(`/api/user-number-libraries/${id}`),
        axios.get(`/api/user-number-librarybooks/${id}`),
      ])
        .then(([response1, response2, response3, response4]) => {
          setUserStats((prevStats) => ({
            ...prevStats,
            numberOfAuthors: response1.data,
            numberOfBooks: response2.data,
            numberOfLibraries: response3.data,
            numberOfLibraryBooks: response4.data,
          }));
          setIsLoading(false);
        })
        .catch((error) => {
          console.log(error);
          setIsLoading(false);
        });
    };

    fetchUser();
    fetchUserStats();
  }, [id]);

  const role = props.roles;

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  const handleSubmit = (event) => {
    event.preventDefault();
    const validationErrors = validateForm(updatedUser);
    if (Object.keys(validationErrors).length === 0) {
      setIsLoading(true);
      axios
        .put(`/api/user-profile/${id}`, updatedUser)
        .then((response) => {
          setUser(response.data);
          setIsLoading(false);
          navigate("/");
        })
        .catch((error) => {
          console.log(error);
          setIsLoading(false);
        });
    } else {
      setErrors(validationErrors);
    }
  };

  const handleInputChange = ({ target: { name, value } }) => {
    setUpdatedUser((prevUser) => ({
      ...prevUser,
      [name]: value.trim(),
    }));
  };

  const validateForm = (user) => {
    return Object.entries(user).reduce((errors, [field, value]) => {
      if (!value.trim()) {
        errors[field] = `${
          field.charAt(0).toUpperCase() + field.slice(1)
        } is required`;
      }
      return errors;
    }, {});
  };

  if (isLoading) {
    return <div>Loading...</div>;
  }

  return (
    <div>
      {role === "ROLE_ADMIN" && (
        <div className="container">
          <h1>Edit Profile</h1>
          <form onSubmit={handleSubmit}>
            <div className="form-group">
              <label htmlFor="bio">Bio:</label>
              <textarea
                className="form-control"
                id="bio"
                name="bio"
                value={updatedUser.bio}
                onChange={handleInputChange}
              />
              {errors.bio && (
                <div className="alert alert-danger">{errors.bio}</div>
              )}
            </div>
            <div className="form-group">
              <label htmlFor="location">Location:</label>
              <input
                type="text"
                className="form-control"
                id="location"
                name="location"
                value={updatedUser.location}
                onChange={handleInputChange}
              />
              {errors.location && (
                <div className="alert alert-danger">{errors.location}</div>
              )}
            </div>
            <div className="form-group">
              <label htmlFor="birthdate">Date of Birth:</label>
              <input
                type="date"
                className="form-control"
                id="birthdate"
                name="birthdate"
                value={updatedUser.birthdate}
                onChange={handleInputChange}
              />
              {errors.birthdate && (
                <div className="alert alert-danger">{errors.birthdate}</div>
              )}
            </div>
            <div className="form-group">
              <label htmlFor="gender">Gender:</label>
              <input
                type="text"
                className="form-control"
                id="gender"
                name="gender"
                value={updatedUser.gender}
                onChange={handleInputChange}
              />
              {errors.gender && (
                <div className="alert alert-danger">{errors.gender}</div>
              )}
            </div>
            <div className="form-group">
              <label htmlFor="maritalStatus">Marital Status:</label>
              <input
                type="text"
                className="form-control"
                id="maritalStatus"
                name="maritalStatus"
                value={updatedUser.maritalStatus}
                onChange={handleInputChange}
              />
              {errors.maritalStatus && (
                <div className="alert alert-danger">{errors.maritalStatus}</div>
              )}
            </div>
            <button type="submit" className="btn btn-primary">
              Save
            </button>
          </form>
        </div>
      )}
      <div className="container">
        <h1>User Profile</h1>
        <p>User ID: {id}</p>
        <p>Bio: {user.bio || "Bio not set up"}</p>
        <p>Location: {user.location || "Location not set up"}</p>
        <p>Date of Birth: {user.birthdate || "Date of Birth not set up"}</p>
        <p>Gender: {user.gender || "Gender not set up"}</p>
        <p>
          Marital Status: {user.maritalStatus || "Marital Status not set up"}
        </p>
        <p>Number of Authors: {userStats.numberOfAuthors}</p>
        <p>Number of Books: {userStats.numberOfBooks}</p>
        <p>Number of Libraries: {userStats.numberOfLibraries}</p>
        <p>Number of Library Books: {userStats.numberOfLibraryBooks}</p>
      </div>
    </div>
  );
}

export default UserProfile;
