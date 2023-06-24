import React, { useState, useEffect } from "react";
import axios from "axios";

const LibraryPage = ({ match }) => {
  const [library, setLibrary] = useState({});

  useEffect(() => {
    const fetchData = async () => {
      const result = await axios(`/api/libraries/${match.params.id}`);
      setLibrary(result.data);
    };
    fetchData();
  }, [match.params.id]);

  return (
    <div className="container">
      <h1 className="mt-5 mb-3">{library.name}</h1>
      <div className="row">
        <div className="col-md-6">
          <p>
            <strong>Description:</strong> {library.description}
          </p>
          <p>
            <strong>Location:</strong> {library.location}
          </p>
          <p>
            <strong>Rating:</strong> {library.rating}
          </p>
          <p>
            <strong>Owner:</strong> {library.owner}
          </p>
        </div>
      </div>
      <h2 className="mt-5 mb-3">Books</h2>
      <ul className="list-group mb-3">
        {library.books &&
          library.books.map((book) => (
            <li key={book.id} className="list-group-item">
              <p>
                <strong>ID:</strong> {book.id}
              </p>
              <p>
                <strong>Borrow Date:</strong> ${book.borrowDate}
              </p>
              <p>
                <strong>Return Date:</strong> {book.returnDate}
              </p>
            </li>
          ))}
      </ul>
    </div>
  );
};

export default LibraryPage;
