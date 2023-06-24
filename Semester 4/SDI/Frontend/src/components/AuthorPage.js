import React, { useState, useEffect } from "react";
import axios from "axios";

const AuthorPage = ({ match }) => {
  const [author, setAuthor] = useState({});

  useEffect(() => {
    const fetchData = async () => {
      const result = await axios(`/api/authors/${match.params.id}`);
      setAuthor(result.data);
    };
    fetchData();
  }, [match.params.id]);

  return (
    <div className="container">
      <h1 className="mt-5 mb-3">{author.name}</h1>
      <div className="row">
        <div className="col-md-6">
          <p>
            <strong>Email:</strong> {author.email}
          </p>
          <p>
            <strong>Country:</strong> {author.country}
          </p>
          <p>
            <strong>Bio:</strong> {author.bio}
          </p>
        </div>
      </div>
      <h2 className="mt-5 mb-3">Books</h2>
      <ul className="list-group mb-3">
        {author.books &&
          author.books.map((book) => (
            <li key={book.id} className="list-group-item">
              <h4>{book.title}</h4>
              <p>
                <strong>Year:</strong> {book.year}
              </p>
              <p>
                <strong>Price:</strong> ${book.price.toFixed(2)}
              </p>
              <p>
                <strong>Rating:</strong> {book.rating}/5
              </p>
            </li>
          ))}
      </ul>
    </div>
  );
};

export default AuthorPage;
