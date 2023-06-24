import React, { useState } from "react";
import { Link } from "react-router-dom";
import axios from "axios";

function AdminPage() {
  const [confirmDeleteAuthors, setConfirmDeleteAuthors] = useState(false);
  const [confirmDeleteBooks, setConfirmDeleteBooks] = useState(false);
  const [confirmDeleteLibraries, setConfirmDeleteLibraries] = useState(false);
  const [confirmDeleteLibraryBooks, setConfirmDeleteLibraryBooks] =
    useState(false);
  const [confirmInsertAuthors, setConfirmInsertAuthors] = useState(false);
  const [confirmInsertBooks, setConfirmInsertBooks] = useState(false);
  const [confirmInsertLibraries, setConfirmInsertLibraries] = useState(false);
  const [confirmInsertLibraryBooks, setConfirmInsertLibraryBooks] =
    useState(false);

  const userString = localStorage.getItem("user");
  const user = JSON.parse(userString);

  const jwtToken = user.jwtToken;

  const handleDeleteAuthors = async () => {
    if (confirmDeleteAuthors) {
      try {
        const response = await axios.post(
          "/api/run-delete-authors-script",
          null,
          {
            headers: {
              Authorization: jwtToken,
            },
          }
        );
        alert(response.data.message);
      } catch (error) {
        console.error(error);
      }
    } else {
      setConfirmDeleteAuthors(true);
    }
  };

  const handleInsertAuthors = async () => {
    if (confirmDeleteAuthors) {
      try {
        const response = await axios.post(
          "/api/run-insert-authors-script",
          null,
          {
            headers: {
              Authorization: jwtToken,
            },
          }
        );
        alert(response.data.message);
      } catch (error) {
        console.error(error);
      }
    } else {
      setConfirmInsertAuthors(true);
    }
  };

  const handleDeleteBooks = async () => {
    if (confirmDeleteBooks) {
      try {
        const response = await axios.post(
          "/api/run-delete-books-script",
          null,
          {
            headers: {
              Authorization: jwtToken,
            },
          }
        );
        alert(response.data.message);
      } catch (error) {
        console.error(error);
      }
    } else {
      setConfirmDeleteBooks(true);
    }
  };

  const handleInsertBooks = async () => {
    if (confirmDeleteBooks) {
      try {
        const response = await axios.post(
          "/api/run-insert-books-script",
          null,
          {
            headers: {
              Authorization: jwtToken,
            },
          }
        );
        alert(response.data.message);
      } catch (error) {
        console.error(error);
      }
    } else {
      setConfirmInsertBooks(true);
    }
  };

  const handleDeleteLibraries = async () => {
    if (confirmDeleteLibraries) {
      try {
        const response = await axios.post(
          "/api/run-delete-libraries-script",
          null,
          {
            headers: {
              Authorization: jwtToken,
            },
          }
        );
        alert(response.data.message);
      } catch (error) {
        console.error(error);
      }
    } else {
      setConfirmDeleteLibraries(true);
    }
  };

  const handleInsertLibraries = async () => {
    if (confirmDeleteLibraries) {
      try {
        const response = await axios.post(
          "/api/run-insert-libraries-script",
          null,
          {
            headers: {
              Authorization: jwtToken,
            },
          }
        );
        alert(response.data.message);
      } catch (error) {
        console.error(error);
      }
    } else {
      setConfirmInsertLibraries(true);
    }
  };

  const handleDeleteLibraryBooks = async () => {
    if (confirmDeleteLibraryBooks) {
      try {
        const response = await axios.post(
          "/api/run-delete-librarybooks-script",
          null,
          {
            headers: {
              Authorization: jwtToken,
            },
          }
        );
        alert(response.data.message);
      } catch (error) {
        console.error(error);
      }
    } else {
      setConfirmDeleteLibraryBooks(true);
    }
  };

  const handleInsertLibraryBooks = async () => {
    if (confirmDeleteLibraryBooks) {
      try {
        const response = await axios.post(
          "/api/run-insert-librarybooks-script",
          null,
          {
            headers: {
              Authorization: jwtToken,
            },
          }
        );
        alert(response.data.message);
      } catch (error) {
        console.error(error);
      }
    } else {
      setConfirmInsertLibraryBooks(true);
    }
  };

  return (
    <div className="container">
      <h1>Admin Page</h1>
      <div>
        <h2>Delete All Authors</h2>
        {confirmDeleteAuthors ? (
          <div>
            <p>Are you sure you want to delete all authors?</p>
            <button className="btn btn-danger" onClick={handleDeleteAuthors}>
              Yes
            </button>
            <button
              className="btn btn-secondary"
              onClick={() => setConfirmDeleteAuthors(false)}
            >
              No
            </button>
          </div>
        ) : (
          <button
            className="btn btn-primary"
            onClick={() => setConfirmDeleteAuthors(true)}
          >
            Delete All Authors
          </button>
        )}
      </div>
      <div>
        <h2>Insert All Authors</h2>
        {confirmInsertAuthors ? (
          <div>
            <p>Are you sure you want to insert all authors?</p>
            <button className="btn btn-danger" onClick={handleInsertAuthors}>
              Yes
            </button>
            <button
              className="btn btn-secondary"
              onClick={() => setConfirmInsertAuthors(false)}
            >
              No
            </button>
          </div>
        ) : (
          <button
            className="btn btn-primary"
            onClick={() => setConfirmInsertAuthors(true)}
          >
            Insert All Authors
          </button>
        )}
      </div>
      <div>
        <h2>Delete All Books</h2>
        {confirmDeleteBooks ? (
          <div>
            <p>Are you sure you want to delete all books?</p>
            <button className="btn btn-danger" onClick={handleDeleteBooks}>
              Yes
            </button>
            <button
              className="btn btn-secondary"
              onClick={() => setConfirmDeleteBooks(false)}
            >
              No
            </button>
          </div>
        ) : (
          <button
            className="btn btn-primary"
            onClick={() => setConfirmDeleteBooks(true)}
          >
            Delete All Books
          </button>
        )}
      </div>
      <div>
        <h2>Insert All Books</h2>
        {confirmInsertBooks ? (
          <div>
            <p>Are you sure you want to insert all authors?</p>
            <button className="btn btn-danger" onClick={handleInsertBooks}>
              Yes
            </button>
            <button
              className="btn btn-secondary"
              onClick={() => setConfirmInsertBooks(false)}
            >
              No
            </button>
          </div>
        ) : (
          <button
            className="btn btn-primary"
            onClick={() => setConfirmInsertBooks(true)}
          >
            Insert All Books
          </button>
        )}
      </div>
      <div>
        <h2>Delete All Libraries</h2>
        {confirmDeleteLibraries ? (
          <div>
            <p>Are you sure you want to delete all libraries?</p>
            <button className="btn btn-danger" onClick={handleDeleteLibraries}>
              Yes
            </button>
            <button
              className="btn btn-secondary"
              onClick={() => setConfirmDeleteLibraries(false)}
            >
              No
            </button>
          </div>
        ) : (
          <button
            className="btn btn-primary"
            onClick={() => setConfirmDeleteLibraries(true)}
          >
            Delete All Libraries
          </button>
        )}
      </div>
      <div>
        <h2>Insert All Libraries</h2>
        {confirmInsertLibraries ? (
          <div>
            <p>Are you sure you want to insert all libraries?</p>
            <button className="btn btn-danger" onClick={handleInsertLibraries}>
              Yes
            </button>
            <button
              className="btn btn-secondary"
              onClick={() => setConfirmInsertLibraries(false)}
            >
              No
            </button>
          </div>
        ) : (
          <button
            className="btn btn-primary"
            onClick={() => setConfirmInsertLibraries(true)}
          >
            Insert All Libraries
          </button>
        )}
      </div>
      <div>
        <h2>Delete All Library Books</h2>
        {confirmDeleteLibraryBooks ? (
          <div>
            <p>Are you sure you want to delete all library books?</p>
            <button
              className="btn btn-danger"
              onClick={handleDeleteLibraryBooks}
            >
              Yes
            </button>
            <button
              className="btn btn-secondary"
              onClick={() => setConfirmDeleteLibraryBooks(false)}
            >
              No
            </button>
          </div>
        ) : (
          <button
            className="btn btn-primary"
            onClick={() => setConfirmDeleteLibraryBooks(true)}
          >
            Delete All Library Books
          </button>
        )}
      </div>
      <div>
        <h2>Insert All Library Books</h2>
        {confirmInsertLibraryBooks ? (
          <div>
            <p>Are you sure you want to insert all library books?</p>
            <button
              className="btn btn-danger"
              onClick={handleInsertLibraryBooks}
            >
              Yes
            </button>
            <button
              className="btn btn-secondary"
              onClick={() => setConfirmInsertLibraryBooks(false)}
            >
              No
            </button>
          </div>
        ) : (
          <button
            className="btn btn-primary"
            onClick={() => setConfirmInsertLibraryBooks(true)}
          >
            Insert All Library Books
          </button>
        )}
      </div>
      <h2>Search Users</h2>
      <Link to="/dashboard/users">
        <button className="btn btn-primary">Search Users</button>
      </Link>

      <h2>Set up Entries per Page</h2>
      <Link to="/dashboard/entries">
        <button className="btn btn-primary">Entries Per Page</button>
      </Link>
    </div>
  );
}

export default AdminPage;
