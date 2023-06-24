import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";

function CreateLibraryBook(props) {
  const [librarybook, setLibraryBook] = useState({
    bookID: "",
    libraryID: "",
  });
  const navigate = useNavigate();

  const role = props.roles;

  const handleSubmit = (event) => {
    event.preventDefault();
    axios
      .post("/api/librarybook", librarybook)
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

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  return (
    <div class="container mt-5">
      <div class="row justify-content-center">
        <div class="col-md-6">
          <h1 class="text-center mb-4">Create LibraryBook</h1>
          <form onSubmit={handleSubmit}>
            <div class="mb-6">
              <label class="form-label" htmlFor="book_id">
                Book ID:
              </label>
              <input
                type="number"
                class="form-control"
                id="book_id"
                name="book_id"
                value={librarybook.bookID}
                onChange={handleInputChange}
              />
            </div>
            <div class="mb-6">
              <label class="form-label" htmlFor="libraryID">
                Email:
              </label>
              <input
                type="number"
                class="form-control"
                id="libraryID"
                name="libraryID"
                value={librarybook.libraryID}
                onChange={handleInputChange}
              />
            </div>
            <button type="submit" class="btn btn-primary">
              Create
            </button>
          </form>
        </div>
      </div>
    </div>
  );
}

export default CreateLibraryBook;
