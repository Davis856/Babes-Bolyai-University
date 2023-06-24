import React, { useState, useEffect } from "react";
import axios from "axios";

const LibraryBookPage = ({ match }) => {
  const [librarybook, setLibraryBook] = useState({});

  useEffect(() => {
    const fetchData = async () => {
      const result = await axios(`/api/librarybook/${match.params.id}`);
      setLibraryBook(result.data);
    };
    fetchData();
  }, [match.params.id]);

  return (
    <div className="container">
      <h1 className="mt-5 mb-3">{librarybook.name}</h1>
      <div className="row">
        <div className="col-md-12">
          <p>
            <strong>Email:</strong> {librarybook.email}
          </p>
          <p>
            <strong>Country:</strong> {librarybook.country}
          </p>
          <p>
            <strong>Bio:</strong> {librarybook.bio}
          </p>
        </div>
      </div>
    </div>
  );
};

export default LibraryBookPage;
