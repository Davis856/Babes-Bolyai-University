// Define the puzzle image parts
const puzzleParts = [
    "image_part_001.jpg",
    "image_part_002.jpg",
    "image_part_003.jpg",
    "image_part_004.jpg",
    "image_part_005.jpg",
    "image_part_006.jpg",
    "image_part_007.jpg",
    "image_part_008.jpg",
    "image_part_009.jpg"
];
  
// Shuffle the puzzle parts
function shuffleArray(array) {
    for (let i = array.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [array[i], array[j]] = [array[j], array[i]];
    }
    return array;
}
  
let firstSelectedCell = null;

function selectCell(cell) {
  if (firstSelectedCell === null) {
    firstSelectedCell = cell;
    cell.style.backgroundColor = "yellow";
  } else {
    if (firstSelectedCell === cell) {
      cell.style.backgroundColor = "";
      firstSelectedCell = null;
    } else {
      const tempImage = firstSelectedCell.style.backgroundImage;
      firstSelectedCell.style.backgroundImage = cell.style.backgroundImage;
      cell.style.backgroundImage = tempImage;
      firstSelectedCell.style.backgroundColor = "";
      firstSelectedCell = null;
      if (checkPuzzle()) {
        alert("Well done!");
      }
    }
  } 
}
  
function checkPuzzle() {
  const orderedParts = puzzleParts.slice().sort();
  for (let i = 0; i < orderedParts.length; i++) {
    const cell = document.getElementById(`cell-${i}`);
    const imageUrl = cell.style.backgroundImage.slice(5, -2);
    if (imageUrl !== orderedParts[i]) {
      return false;
    }
  }
  return true;
}
  
function setPuzzle() {
  const shuffledParts = shuffleArray(puzzleParts);
  for (let i = 0; i < shuffledParts.length; i++) {
      const cell = document.getElementById(`cell-${i}`);
      cell.style.backgroundImage = `url(${shuffledParts[i]})`;
      cell.classList.add("puzzle-cell"); // add the "puzzle-cell" class to the cell
      cell.addEventListener("click", () => {
      selectCell(cell);
      });
  }
}
  

// Set up the puzzle and add event listener to the check puzzle button
setPuzzle();
const checkPuzzleButton = document.getElementById("check-puzzle");
checkPuzzleButton.addEventListener("click", shuffleArray(puzzleParts));
  