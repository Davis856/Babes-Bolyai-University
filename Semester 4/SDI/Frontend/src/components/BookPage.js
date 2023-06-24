import React, { useState, useEffect, useCallback } from "react";
import axios from "axios";
import { useParams } from "react-router-dom";

function BookPage() {
  const { id } = useParams();
  const [book, setBook] = useState(null);

  const fetchBook = useCallback(() => {
    axios
      .get(`/api/books/${id}`)
      .then((response) => {
        setBook(response.data);
      })
      .catch((error) => console.log(error));
  }, [id]);

  useEffect(() => {
    fetchBook();
  }, [fetchBook]);

  if (!book) {
    return <div>Loading...</div>;
  }

  return (
    <div className="container">
      <h1 className="mt-5 mb-3">{book.title}</h1>
      <div className="row">
        <div className="col-6">
          <p>
            <strong>Author:</strong> {book.author.name}
          </p>
        </div>
        <div className="col-6">
          <p>
            <strong>Year:</strong> {book.year}
          </p>
        </div>
      </div>
      <div className="row">
        <div className="col-6">
          <p>
            <strong>Price:</strong> ${book.price.toFixed(2)}
          </p>
        </div>
        <div className="col-6">
          <p>
            <strong>Rating:</strong> {book.rating}/5
          </p>
        </div>
      </div>
      <p>
        <strong>Libraries:</strong>{" "}
        {book.libraries.map((library) => library.libraryID).join(", ")}
      </p>
    </div>
  );
}

export default BookPage;
