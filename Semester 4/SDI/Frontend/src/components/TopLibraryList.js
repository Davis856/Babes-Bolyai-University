import React, { useState, useEffect } from "react";
import axios from "axios";

const TopLibraryList = () => {
  const [libraries, setLibraries] = useState([]);
  const [page, setPage] = useState(0);
  const [size, setSize] = useState(10);

  useEffect(() => {
    const fetchLibraries = async () => {
      const response = await axios.get(
        `/api/libraries/getLibrariesTop?page=${page}&size=${size}`
      );
      setLibraries(response.data.content);
    };
    fetchLibraries();
  }, [page, size]);

  const handlePrevious = () => {
    if (page > 0) {
      setPage(page - 1);
    }
  };

  const handleNext = () => {
    setPage(page + 1);
  };

  return (
    <div className="container">
      <h2 className="mb-4">Libraries</h2>
      <table className="table table-striped">
        <thead>
          <tr>
            <th>ID</th>
            <th>Name</th>
            <th>Number of Books</th>
          </tr>
        </thead>
        <tbody>
          {libraries.map((library) => (
            <tr key={library.libraryId}>
              <td>{library.libraryId}</td>
              <td>{library.libraryName}</td>
              <td>{library.booksCount}</td>
            </tr>
          ))}
        </tbody>
      </table>
      <div className="d-flex justify-content-between align-items-center">
        <button
          className="btn btn-primary"
          onClick={handlePrevious}
          disabled={page === 0}
        >
          Previous
        </button>
        <button
          className="btn btn-primary"
          onClick={handleNext}
          disabled={libraries.length < size}
        >
          Next
        </button>
      </div>
    </div>
  );
};

export default TopLibraryList;
