import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";

function CreateBook(props) {
  const [book, setBook] = useState({
    title: "",
    year: "",
    rating: "",
    price: "",
    authorId: "",
  });

  const role = props.roles;

  const [errors, setErrors] = useState({});

  const navigate = useNavigate();

  const handleSubmit = (event) => {
    event.preventDefault();

    const validationErrors = {};

    if (!book.title) {
      validationErrors.title = "Title is required";
    }

    if (!book.year) {
      validationErrors.year = "Year is required";
    }

    if (!book.rating) {
      validationErrors.rating = "Rating is required";
    }

    if (!book.price) {
      validationErrors.price = "Price is required";
    }

    if (!book.authorId) {
      validationErrors.authorId = "Author ID is required";
    }

    if (Object.keys(validationErrors).length > 0) {
      setErrors(validationErrors);
      return;
    }

    axios
      .post("/api/books", book)
      .then((response) => {
        console.log(response);
        navigate("/books");
      })
      .catch((error) => console.log(error));
  };

  const handleInputChange = (event) => {
    const { name, value } = event.target;
    setBook((prevBook) => ({
      ...prevBook,
      [name]: value,
    }));
  };

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  return (
    <div className="container">
      <h1>Create Book</h1>
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
          <label htmlFor="authorId">Author ID:</label>
          <input
            type="number"
            className="form-control"
            id="authorId"
            name="authorId"
            value={book.authorId}
            onChange={handleInputChange}
          />
          {errors.authorId && (
            <div className="alert alert-danger">{errors.authorId}</div>
          )}
        </div>
        <button type="submit" className="btn btn-primary">
          Create
        </button>
      </form>
    </div>
  );
}

export default CreateBook;
