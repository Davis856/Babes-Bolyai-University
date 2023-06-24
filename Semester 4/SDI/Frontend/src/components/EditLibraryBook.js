import React, { useState, useEffect } from "react";
import { useNavigate, useParams } from "react-router-dom";
import axios from "axios";

function EditLibraryBook(props) {
  const [librarybook, setLibraryBook] = useState({
    bookID: "",
    libraryID: "",
  });

  const navigate = useNavigate();
  const { id } = useParams();

  useEffect(() => {
    fetchLibraryBook();
  });

  const userString = localStorage.getItem("user");
  const user = JSON.parse(userString);

  const jwtToken = user.jwtToken;

  const fetchLibraryBook = () => {
    axios
      .get(`/api/librarybook/${id}`)
      .then((response) => setLibraryBook(response.data))
      .catch((error) => console.log(error));
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    axios
      .put(`/api/librarybook/${id}`, librarybook, {
        headers: {
          Authorization: jwtToken,
        },
      })
      .then((response) => {
        console.log(response);
        navigate("/librarybook");
      })
      .catch((error) => console.log(error));
  };

  const handleInputChange = (event) => {
    const { name, value } = event.target;
    setLibraryBook((prevLibraryBook) => ({
      ...prevLibraryBook,
      [name]: value,
    }));
  };

  const role = props.roles;

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  return (
    <div class="container">
      <h1>Edit LibraryBook</h1>
      <form onSubmit={handleSubmit}>
        <div class="form-group">
          <label htmlFor="book_id">Book ID:</label>
          <input
            type="number"
            class="form-control"
            id="book_id"
            name="book_id"
            value={librarybook.bookID}
            onChange={handleInputChange}
          />
        </div>
        <div class="form-group">
          <label htmlFor="library_id">Library ID:</label>
          <input
            type="number"
            class="form-control"
            id="library_id"
            name="library_id"
            value={librarybook.libraryID}
            onChange={handleInputChange}
          />
        </div>
        <button type="submit" class="btn btn-primary">
          Update
        </button>
      </form>
    </div>
  );
}

export default EditLibraryBook;
