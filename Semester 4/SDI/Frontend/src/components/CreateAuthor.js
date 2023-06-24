import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";

function CreateAuthor(props) {
  const [author, setAuthor] = useState({
    name: "",
    email: "",
    bio: "",
    country: "",
  });
  const [errors, setErrors] = useState({});

  const role = props.roles;

  const navigate = useNavigate();

  const handleSubmit = (event) => {
    event.preventDefault();

    // Validate form data
    const errors = validate(author);
    if (Object.keys(errors).length > 0) {
      setErrors(errors);
      return;
    }

    axios
      .post("/api/authors", author)
      .then((response) => {
        console.log(response);
        navigate("/authors");
      })
      .catch((error) => console.log(error));
  };

  const handleInputChange = (event) => {
    const { name, value } = event.target;
    setAuthor((prevAuthor) => ({
      ...prevAuthor,
      [name]: value,
    }));
  };

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  const validate = (data) => {
    const errors = {};

    if (!data.name.trim()) {
      errors.name = "Name is mandatory";
    }

    if (!data.email.trim()) {
      errors.email = "Email is mandatory";
    } else if (!/\S+@\S+\.\S+/.test(data.email)) {
      errors.email = "Email should be valid";
    }

    return errors;
  };

  return (
    <div class="container mt-5">
      <div class="row justify-content-center">
        <div class="col-md-6">
          <h1 class="text-center mb-4">Create Author</h1>
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
                value={author.name}
                onChange={handleInputChange}
              />
              {errors.name && <div className="text-danger">{errors.name}</div>}
            </div>
            <div class="mb-3">
              <label class="form-label" htmlFor="email">
                Email:
              </label>
              <input
                type="email"
                class="form-control"
                id="email"
                name="email"
                value={author.email}
                onChange={handleInputChange}
              />
              {errors.email && (
                <div className="text-danger">{errors.email}</div>
              )}
            </div>
            <div class="mb-3">
              <label class="form-label" htmlFor="bio">
                Bio:
              </label>
              <textarea
                class="form-control"
                id="bio"
                name="bio"
                value={author.bio}
                onChange={handleInputChange}
              ></textarea>
            </div>
            <div class="mb-3">
              <label class="form-label" htmlFor="country">
                Country:
              </label>
              <input
                type="text"
                class="form-control"
                id="country"
                name="country"
                value={author.country}
                onChange={handleInputChange}
              />
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

export default CreateAuthor;
