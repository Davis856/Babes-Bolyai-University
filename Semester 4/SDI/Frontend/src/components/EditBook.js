import React, { useState, useEffect } from "react";
import { useNavigate, useParams } from "react-router-dom";
import axios from "axios";

function EditBook(props) {
  const [book, setBook] = useState({
    title: "",
    year: "",
    rating: "",
    price: "",
    author: {
      id: "",
    },
  });

  const [errors, setErrors] = useState({
    title: "",
    year: "",
    rating: "",
    price: "",
    author: {
      id: "",
    },
  });

  const navigate = useNavigate();
  const { id } = useParams();

  useEffect(() => {
    fetchBook();
  });

  const role = props.roles;

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  const userString = localStorage.getItem("user");
  const user = JSON.parse(userString);

  const jwtToken = user.jwtToken;

  const fetchBook = () => {
    axios
      .get(`/api/books/${id}`)
      .then((response) => setBook(response.data))
      .catch((error) => console.log(error));
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    const validationErrors = validateBook(book);
    if (Object.keys(validationErrors).length === 0) {
      axios
        .put(`/api/books/${id}`, book, {
          headers: {
            Authorization: jwtToken,
          },
        })
        .then((response) => {
          console.log(response);
          navigate("/books");
        })
        .catch((error) => console.log(error));
    } else {
      setErrors(validationErrors);
    }
  };

  const handleInputChange = (event) => {
    const { name, value } = event.target;
    setBook((prevBook) => ({
      ...prevBook,
      [name]: value,
    }));
  };

  const validateBook = () => {
    let errors = {};

    if (!book.title) {
      errors.title = "Title is required";
    }

    if (!book.year) {
      errors.year = "Year is required";
    } else if (book.year < 1900 || book.year > 2023) {
      errors.year = "Year must be between 1900 and 2023";
    }

    if (!book.rating) {
      errors.rating = "Rating is required";
    } else if (book.rating < 1 || book.rating > 5) {
      errors.rating = "Rating must be between 1 and 5";
    }

    if (!book.price) {
      errors.price = "Price is required";
    } else if (book.price < 0) {
      errors.price = "Price must be a positive number";
    }

    if (!book.author.id) {
      errors.author.id = "Author ID is required";
    } else if (book.author.id < 1) {
      errors.author.id = "Author ID must be a positive number";
    }

    setErrors(errors);
    return Object.keys(errors).length === 0;
  };

  return (
    <div className="container">
      <h1>Edit Book</h1>
      <form onSubmit={handleSubmit}>
        <div className="form-group">
          <label htmlFor="title">Title:</label>
          <input
            type="text"
            className="form-control"
            id="title"
            name="title"
            value={book.title}
            onChange={handleInputChange}
          />
          {errors.title && (
            <div className="alert alert-danger">{errors.title}</div>
          )}
        </div>
        <div className="form-group">
          <label htmlFor="year">Year:</label>
          <input
            type="number"
            className="form-control"
            id="year"
            name="year"
            value={book.year}
            onChange={handleInputChange}
          />
          {errors.year && (
            <div className="alert alert-danger">{errors.year}</div>
          )}
        </div>
        <div className="form-group">
          <label htmlFor="price">Price:</label>
          <input
            type="number"
            className="form-control"
            id="price"
            name="price"
            value={book.price}
            onChange={handleInputChange}
          />
          {errors.price && (
            <div className="alert alert-danger">{errors.price}</div>
          )}
        </div>
        <div className="form-group">
          <label htmlFor="rating">Rating:</label>
          <input
            type="number"
            className="form-control"
            id="rating"
            name="rating"
            value={book.rating}
            onChange={handleInputChange}
          />
          {errors.rating && (
            <div className="alert alert-danger">{errors.rating}</div>
          )}
        </div>
        <div className="form-group">
          <label htmlFor="author.id">Author ID:</label>
          <input
            type="number"
            className="form-control"
            id="author.id"
            name="author.id"
            value={book.author.id}
            onChange={handleInputChange}
          />
          {errors.author.id && (
            <div className="alert alert-danger">{errors.author.id}</div>
          )}
        </div>
        <button type="submit" className="btn btn-primary">
          Save
        </button>
      </form>
    </div>
  );
}

export default EditBook;
