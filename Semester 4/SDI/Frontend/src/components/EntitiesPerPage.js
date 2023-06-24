import React, { useState } from 'react';

function EntitiesPerPage({ setItemsPerPage }) {
  const [modifiedItemsPerPage, setModifiedItemsPerPage] = useState(10);

  return (
    <div>
      <label>Entities Per Page:</label>
      <input
        type="number"
        value={modifiedItemsPerPage}
        onChange={(e) => {
          const value = parseInt(e.target.value);
          setModifiedItemsPerPage(value);
          setItemsPerPage(value);
        }}
      />
    </div>
  );
}

export default EntitiesPerPage;
