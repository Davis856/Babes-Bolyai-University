import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";

function CreateLibrary(props) {
  const [library, setLibrary] = useState({
    name: "",
    description: "",
    location: "",
    rating: 0,
    owner: "",
  });
  const [errors, setErrors] = useState({});

  const role = props.roles;

  const navigate = useNavigate();

  const handleSubmit = (event) => {
    event.preventDefault();

    // Validate form data
    const errors = validate(library);
    if (Object.keys(errors).length > 0) {
      setErrors(errors);
      return;
    }

    axios
      .post("/api/libraries", library)
      .then((response) => {
        console.log(response);
        navigate("/libraries");
      })
      .catch((error) => console.log(error));
  };

  const handleInputChange = (event) => {
    const { name, value } = event.target;
    setLibrary((prevLibrary) => ({
      ...prevLibrary,
      [name]: value,
    }));
  };

  const validate = (data) => {
    const errors = {};

    if (!data.name.trim()) {
      errors.name = "Name is mandatory";
    }

    if (!data.description.trim()) {
      errors.description = "Description is mandatory";
    }

    if (!data.location.trim()) {
      errors.location = "Location is mandatory";
    }

    if (!data.owner.trim()) {
      errors.owner = "Owner is mandatory";
    }

    return errors;
  };

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  return (
    <div class="container mt-5">
      <div class="row justify-content-center">
        <div class="col-md-6">
          <h1 class="text-center mb-4">Create Library</h1>
          <form onSubmit={handleSubmit}>
            <div class="mb-3">
              <label class="form-label" htmlFor="name">
                Name:
              </label>
              <input
                type="text"
                class="form-control"
                id="name"
                name="name"
                value={library.name}
                onChange={handleInputChange}
              />
              {errors.name && <div className="text-danger">{errors.name}</div>}
            </div>
            <div class="mb-3">
              <label class="form-label" htmlFor="description">
                Description:
              </label>
              <textarea
                class="form-control"
                id="description"
                name="description"
                value={library.description}
                onChange={handleInputChange}
              ></textarea>
              {errors.description && (
                <div className="text-danger">{errors.description}</div>
              )}
            </div>
            <div class="mb-3">
              <label class="form-label" htmlFor="location">
                Location:
              </label>
              <input
                type="text"
                class="form-control"
                id="location"
                name="location"
                value={library.location}
                onChange={handleInputChange}
              />
              {errors.location && (
                <div className="text-danger">{errors.location}</div>
              )}
            </div>
            <div class="mb-3">
              <label class="form-label" htmlFor="rating">
                Rating:
              </label>
              <input
                type="number"
                class="form-control"
                id="rating"
                name="rating"
                value={library.rating}
                onChange={handleInputChange}
              />
            </div>
            <div class="mb-3">
              <label class="form-label" htmlFor="owner">
                Owner:
              </label>
              <input
                type="text"
                class="form-control"
                id="owner"
                name="owner"
                value={library.owner}
                onChange={handleInputChange}
              />
              {errors.owner && (
                <div className="text-danger">{errors.owner}</div>
              )}
            </div>
            <button type="submit" class="btn btn-primary">
              Create
            </button>
          </form>
        </div>
      </div>
    </div>
  );
}

export default CreateLibrary;
