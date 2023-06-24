import React, { useState } from "react";

function DeleteLibrary(props) {
  const { library, handleDelete } = props;
  const [showConfirmDialog, setShowConfirmDialog] = useState(false);

  const role = props.roles;

  if (role === "ROLE_ANONYMOUS") {
    window.location.href = "/";
    return null;
  }

  const handleConfirm = () => {
    handleDelete(library.id);
    setShowConfirmDialog(false);
  };

  const handleCancel = () => {
    setShowConfirmDialog(false);
  };

  const handleDeleteClick = () => {
    setShowConfirmDialog(true);
  };

  return (
    <>
      {showConfirmDialog && (
        <div className="alert alert-danger">
          <p>Are you sure you want to delete {library.name}?</p>
          <button className="btn btn-danger mr-2" onClick={handleConfirm}>
            Yes
          </button>
          <button className="btn btn-secondary" onClick={handleCancel}>
            No
          </button>
        </div>
      )}
      <button className="btn btn-danger" onClick={handleDeleteClick}>
        Delete
      </button>
    </>
  );
}

export default DeleteLibrary;
