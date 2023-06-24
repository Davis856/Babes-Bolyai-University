import React, { useState, useEffect, useCallback } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";
import DeleteLibrary from "./DeleteLibrary";

function LibraryList(props) {
  const [libraries, setLibraries] = useState([]);
  const [currentPage, setCurrentPage] = useState(0);
  const itemsPerPage = props.itemsPerPage;
  const navigate = useNavigate();

  const role = props.roles;

  const fetchLibraries = useCallback(() => {
    axios
      .get(`/api/libraries?page=${currentPage}&size=${itemsPerPage}`)
      .then((response) => {
        const sortedLibraries = response.data.content.sort(
          (a, b) => a.id - b.id
        );
        setLibraries(sortedLibraries);
        setCurrentPage(response.data.number);
      })
      .catch((error) => console.log(error));
  }, [currentPage, itemsPerPage]);

  useEffect(() => {
    fetchLibraries();
  }, [fetchLibraries]);

  const userString = localStorage.getItem("user");
  const user = JSON.parse(userString);

  const jwtToken = user.jwtToken;

  const handleEdit = (libraryId) => {
    navigate(`/libraries/${libraryId}/edit`);
  };

  const handleDelete = (libraryId) => {
    axios
      .delete(`/api/libraries/${libraryId}`, {
        headers: {
          Authorization: jwtToken,
        },
      })
      .then((response) => {
        console.log(response);
        fetchLibraries();
      })
      .catch((error) => console.log(error));
  };

  const handleCreate = () => {
    navigate(`/libraries/create`);
  };

  const [totalLibraries, setTotalLibraries] = useState(0);
  useEffect(() => {
    axios
      .get("/api/libraries/count")
      .then((response) => {
        setTotalLibraries(response.data);
      })
      .catch((error) => console.log(error));
  }, []);

  const totalPages = Math.max(1, Math.ceil(totalLibraries / itemsPerPage));

  const handleNextPage = () => {
    setCurrentPage(Math.min(currentPage + 1, totalPages - 1));
  };

  const handlePrevPage = () => {
    setCurrentPage(Math.max(currentPage - 1, 0));
  };

  const handleJump = (jump) => {
    setCurrentPage(Math.max(Math.min(currentPage + jump, totalPages - 1), 0));
  };

  const handleLast = () => {
    setCurrentPage(totalPages - 1);
  };

  const handleFirst = () => {
    setCurrentPage(0);
  };

  const startIdx = currentPage * itemsPerPage;
  const endIdx = Math.min(startIdx + itemsPerPage, totalLibraries);

  return (
    <div className="container">
      <h1 className="mt-5 mb-3">Library List</h1>
      {role !== "ROLE_ANONYMOUS" && (
        <button className="btn btn-primary" onClick={handleCreate}>
          Create Library
        </button>
      )}
      <button
        className="btn btn-secondary me-3"
        onClick={() => navigate("/libraries/getLibrariesTop?page=0&size=100")}
      >
        Top Libraries By Books
      </button>
      <table className="table">
        <thead>
          <tr>
            <th>Name</th>
            <th>Description</th>
            <th>Location</th>
            <th>Rating</th>
            <th>Owner</th>
            <th>Books</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {libraries.map((library) => (
            <tr key={library.id}>
              <td>{library.name}</td>
              <td>{library.description}</td>
              <td>{library.location}</td>
              <td>{library.rating}</td>
              <td>{library.owner}</td>
              <td>{library.booksCount}</td>
              <td>
                {(role.includes("ROLE_ADMIN") ||
                  (role === "ROLE_USER" && library.addedByCurrentUser) ||
                  role === "ROLE_MODERATOR") && (
                  <button
                    className="btn btn-primary me-2"
                    onClick={() => handleEdit(library.id)}
                  >
                    Edit
                  </button>
                )}
                {(role.includes("ROLE_ADMIN") ||
                  (role === "ROLE_USER" && library.addedByCurrentUser) ||
                  role === "ROLE_MODERATOR") && (
                  <DeleteLibrary
                    library={library}
                    handleDelete={handleDelete}
                  />
                )}
              </td>
            </tr>
          ))}
        </tbody>
      </table>
      <div className="d-flex justify-content-between align-items-center">
        <p>
          Showing {startIdx + 1}-{endIdx} of {totalLibraries} libraries
        </p>
        <div>
          <button className="btn btn-secondary me-2" onClick={handlePrevPage}>
            Prev
          </button>
          <button className="btn btn-secondary me-2" onClick={handleNextPage}>
            Next
          </button>
        </div>
        <div>
          <button
            className="btn btn-secondary me-2"
            disabled={currentPage === 0}
            onClick={handleFirst}
          >
            First
          </button>
          <button
            className="btn btn-secondary me-2"
            disabled={currentPage === 0}
            onClick={handlePrevPage}
          >
            Previous
          </button>
          <button
            className="btn btn-secondary me-2"
            disabled={currentPage >= totalPages - 1}
            onClick={handleNextPage}
          >
            Next
          </button>
          <button
            className="btn btn-secondary me-2"
            onClick={() => handleJump(-1000)}
          >
            -1000
          </button>
          <button
            className="btn btn-secondary me-2"
            onClick={() => handleJump(-100)}
          >
            -100
          </button>
          <button
            className="btn btn-secondary me-2"
            onClick={() => handleJump(100)}
          >
            +100
          </button>
          <button
            className="btn btn-secondary me-2"
            onClick={() => handleJump(1000)}
          >
            +1000
          </button>
          <button
            className="btn btn-secondary me-2"
            disabled={currentPage === totalPages - 1}
            onClick={handleLast}
          >
            Last
          </button>
        </div>
      </div>
    </div>
  );
}

export default LibraryList;
