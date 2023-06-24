import React, { useState, useEffect, useCallback } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";
import DeleteLibraryBook from "./DeleteLibraryBook";

function LibraryBookList(props) {
  const [librarybook, setLibraryBooks] = useState([]);
  const [currentPage, setCurrentPage] = useState(0);
  const itemsPerPage = props.itemsPerPage;
  const navigate = useNavigate();

  const role = props.roles;

  const fetchLibraryBooks = useCallback(() => {
    axios
      .get(`/api/librarybook?page=${currentPage}&size=${itemsPerPage}`)
      .then((response) => {
        const sortedLibraryBooks = response.data.content.sort(
          (a, b) => a.id - b.id
        );
        setLibraryBooks(sortedLibraryBooks);
        setCurrentPage(response.data.number);
      })
      .catch((error) => console.log(error));
  }, [currentPage, itemsPerPage]);

  useEffect(() => {
    fetchLibraryBooks();
  }, [fetchLibraryBooks]);

  const userString = localStorage.getItem("user");
  const user = JSON.parse(userString);

  const jwtToken = user.jwtToken;

  const handleEdit = (librarybookId) => {
    navigate(`/librarybook/${librarybookId}/edit`);
  };

  const handleDelete = (librarybookId) => {
    axios
      .delete(`/api/librarybook/${librarybookId}`, {
        headers: {
          Authorization: jwtToken,
        },
      })
      .then((response) => {
        console.log(response);
        fetchLibraryBooks();
      })
      .catch((error) => console.log(error));
  };

  const handleCreate = () => {
    navigate(`/librarybook/create`);
  };

  const [totalLibraryBooks, setTotalLibraryBooks] = useState(0);
  useEffect(() => {
    axios
      .get("/api/librarybook/count")
      .then((response) => {
        setTotalLibraryBooks(response.data);
      })
      .catch((error) => console.log(error));
  }, []);

  const totalPages = Math.max(1, Math.ceil(totalLibraryBooks / itemsPerPage));

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
  const endIdx = Math.min(startIdx + itemsPerPage, totalLibraryBooks);

  return (
    <div className="container">
      <h1 className="mt-5 mb-3">LibraryBook List</h1>
      {role !== "ROLE_ANONYMOUS" && (
        <button className="btn btn-primary" onClick={handleCreate}>
          Create LibraryBook
        </button>
      )}
      <table className="table">
        <thead>
          <tr>
            <th>Book Title</th>
            <th>Library Name</th>
            <th>Borrow Date</th>
            <th>Return Date</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {librarybook.map((librarybook) => (
            <tr key={librarybook.id}>
              <td>{librarybook.bookTitle}</td>
              <td>{librarybook.libraryName}</td>
              <td>{librarybook.borrowDate}</td>
              <td>{librarybook.returnDate}</td>
              <td>
                {(role.includes("ROLE_ADMIN") ||
                  (role === "ROLE_USER" && librarybook.addedByCurrentUser) ||
                  role === "ROLE_MODERATOR") && (
                  <button
                    className="btn btn-primary me-2"
                    onClick={() => handleEdit(librarybook.id)}
                  >
                    Edit
                  </button>
                )}
                {(role.includes("ROLE_ADMIN") ||
                  (role === "ROLE_USER" && librarybook.addedByCurrentUser) ||
                  role === "ROLE_MODERATOR") && (
                  <DeleteLibraryBook
                    librarybook={librarybook}
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
          Showing {startIdx + 1}-{endIdx} of {totalLibraryBooks} LibraryBooks
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

export default LibraryBookList;
