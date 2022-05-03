#include <stdio.h>
#include <stdlib.h>

// Austin Roach
// CS 151

// Tresure Hunt Prep
// Implements dig(), show(), reveal(), and setByOffset()

// Global Variables
int rows = 8;
int columns = 8;
int cells = rows * columns;
int maxIndex = cells - 1;
int maxRow = rows - 1;
int maxColumn = columns - 1;

// Gem Globals

int bronzeNum = 11;
int silverNum = 12;
int goldNum = 13;
int rubiesNum = 14;
int vibraniumNum = 15;

int bronzeLength = 5;
int silverLength = 4;
int goldLength = 3;
int rubiesLength = 2;
int vibraniumLength = 1;

// Helper accepts 2D row, column parameters, returns corresponding 1D array
// index
int flatten(int row, int column) { return (row * columns) + column; }

void unflattenPrint(int coord) {
  int column = coord % columns;
  int row = (coord - column) / columns;
  printf("Row: #%d, Column: #%d", row, column);
}
// Helper - Prints cleanly formatted grid
void printGrid(int *grid) {
  printf("Printing Grid: \n");
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      int cellNum = flatten(row, column);
      printf("[");
      if (grid[cellNum] > -2) {
        printf(" ");
      }
      if (grid[cellNum] == 0) {
        printf(" ");
      }

      printf("%d]", grid[cellNum]);
    }
    printf("\n");
  }
  printf("\n");
}

// Cipher method. Does not modify array.
// 0...max_int prints '-'
// -1 prints 'X'
// Other negatives print '@'
void show(int *arr) {
  printf("Show Method: \n0 is '-' \n-1 is 'X' \nOther negatives are '@' "
         "\nPositives are '-'\n");
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      int cellNumber = flatten(row, column);
      int cell = arr[cellNumber];
      if (cell == -1) {
        printf("[ X ]");
      } else if (cell < -1) {
        printf("[ @ ]");
      } else {
        printf("[ - ]");
      }
    }
    printf("\n");
  }
  printf("\n");
}
// Cipher method. Does not modify array.
// 0 prints '-'
// -1 prints 'X'
// 11-15 print letters 'a-e'
// -(11-15) print letters 'A-E'
void reveal(int *arr) {
  printf("Reveal Method:\n0 is '-'\n-1 is 'X'\n11-15 are letters 'a-e' "
         "respectively\n-(11 - 15) are letters 'A-E' respectively\n");
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      int cellNumber = flatten(row, column);
      int cell = arr[cellNumber];
      printf("[ ");
      if (cell == 0) {
        printf("-");
      } else if (cell == -1) {
        printf("X");
      } else if (cell == -11) {
        printf("A");
      } else if (cell == -12) {
        printf("B");
      } else if (cell == -13) {
        printf("C");
      } else if (cell == -14) {
        printf("D");
      } else if (cell == -15) {
        printf("E");
      } else if (cell == 11) {
        printf("a");
      } else if (cell == 12) {
        printf("b");
      } else if (cell == 13) {
        printf("c");
      } else if (cell == 14) {
        printf("d");
      } else if (cell == 15) {
        printf("e");
      } else {
        printf("%d", cell);
      }
      printf(" ]");
    }
    printf("\n");
  }
  printf("\n");
}

// Modifies array. If the cell was 0, it is now -1.
// If the cell was positive, it is now negative.
void dig(int *arr, int row, int column) {
  printf("Dig Method:\nModifies our array\nIf the cell was 0, it is now -1\nIf "
         "the cell was positive, it is now negative\nModifying Column #%d, Row "
         "#%d\n",
         column, row);

  int coord = flatten(row, column);

  if (arr[coord] == 0) {
    arr[coord] = -1;
  }
  if (arr[coord] > 0) {
    arr[coord] *= -1;
  }
  printGrid(arr);
}
// Tests dig method by iteratively 'digging' all cells.
// CAUTION: Produces a lot of console output - one grid is printed per
// modification
void digAll(int *arr) {
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      dig(arr, row, column);
    }
  }
}

// Checks cell to ensure it is not occupied by any other treasure chests.
// Returns false if treasure is found. True if unoccupied.
bool checkCell(int *array, int coord, int value) {
  return !(array[coord] != 0 && array[coord] != -1 && array[coord] != value);
}
// Checks a subarray to ensure all cells are available for treasure placement
bool checkPlacement(int *array, int row, int column, int repeats, int value,
                    bool horizontal) {
  int coord = flatten(row, column);
  if (maxRow < row) {
    printf("Error: Starting row out of range\n");
  }
  if (maxColumn < column) {
    printf("Error: Starting column out of range\n");
  }
  if (maxRow < row || maxColumn < column) {
    printf("\n");
    return false;
  }
  if (horizontal) {
    int diff = (column + repeats) - columns;
    if (diff > 0) {
      printf("Error: chest too wide for placement by %d cell", diff);
      if (diff > 1) {
        printf("s");
      }
      printf("\n\n");
      return false;
    }
    for (int i = 0; i < repeats; i++) {
      if (!checkCell(array, coord, value)) {
        printf(
            "Error: There is already another type of chest in this cell\n\n");
        return false;
      }
      coord++;
    }
  } else { // if vertical
    int diff = (row + repeats) - rows;
    if (diff > 0) {
      printf("Error: chest too tall for placement by %d cell", diff);
      if (diff > 1) {
        printf("s");
      }
      printf("\n\n");
      return false;
    }
    for (int i = 0; i < repeats; i++) {
      if (!checkCell(array, coord, value)) {
        printf(
            "Error: There is already another type of chest in this cell\n\n");
        return false;
      }
      coord += columns;
    }
  }
  return true;
}

int placeChest(int *array, int row, int column, int repeats, int value,
               bool horizontal) {
  int counter = 0;
  int coord = flatten(row, column);

  if (checkPlacement(array, row, column, repeats, value, horizontal)) {
    while (repeats > 0) {
      if (array[coord] != value) {
        array[coord] = value;
        counter++;
      }
      if (horizontal) {
        coord++;
      } else {
        coord += columns;
      }
      repeats--;
    }
    return counter;
  }
  return -1;
}

void placeChestTest(int *array, int row, int column, int repeats, int init,
                    bool horizontal) {

  printf("Place Chest Method:\nStarting cell: Row #%d, Column #%d\nWriting %d "
         "over cell data %d times ",
         row, column, init, repeats);

  if (horizontal) {
    printf("horizontally\n");
  } else {
    printf("vertically\n");
  }
  if (!checkPlacement(array, row, column, repeats, init, horizontal)) {
    return;
  }

  int modified = placeChest(array, row, column, repeats, init, horizontal);
  printGrid(array);
  if (modified == 1) {
    printf("1 cell modified\n\n");
  } else if (modified == -1) {
    printf("Invalid Parameter, no modifications made\n\n");
  } else {
    printf("%d cells modified\n\n", modified);
  }
}

void placeChestTestSuite(int *arr) {
  // placeChest testing variables for valid, vertical test
  int chestRow = 6;
  int chestColumn = 0;
  int chestValue = 11;
  int chestRepeats = 8;
  bool chestHorizontal = true;

  printf("TEST: Valid horizontal placement\n\n");
  placeChestTest(arr, chestRow, chestColumn, chestRepeats, chestValue,
                 chestHorizontal);

  printf("TEST: Valid vertical placement\n\n");

  chestRow = 0;
  chestColumn = 2;
  chestValue = 11;
  chestRepeats = 5;
  chestHorizontal = false;

  placeChestTest(arr, chestRow, chestColumn, chestRepeats, chestValue,
                 chestHorizontal);

  printf("TEST: Starting column out of range:\n\n");

  chestRow = 0;
  chestColumn = 10;
  chestValue = 11;
  chestRepeats = 5;
  chestHorizontal = false;

  placeChestTest(arr, chestRow, chestColumn, chestRepeats, chestValue,
                 chestHorizontal);

  printf("TEST: Starting row out of range:\n\n");

  chestRow = 10;
  chestColumn = 0;
  chestValue = 11;
  chestRepeats = 5;
  chestHorizontal = false;

  placeChestTest(arr, chestRow, chestColumn, chestRepeats, chestValue,
                 chestHorizontal);

  printf("TEST: Starting row and column out of range:\n\n");

  chestRow = 10;
  chestColumn = 10;
  chestValue = 11;
  chestRepeats = 5;
  chestHorizontal = false;

  placeChestTest(arr, chestRow, chestColumn, chestRepeats, chestValue,
                 chestHorizontal);

  printf("TEST: Horizontal treasure exceeds number of columns:\n\n");

  chestRow = 1;
  chestColumn = 0;
  chestValue = 11;
  chestRepeats = 9;
  chestHorizontal = true;

  placeChestTest(arr, chestRow, chestColumn, chestRepeats, chestValue,
                 chestHorizontal);

  printf("TEST: Vertical treasure exceeds number of rows:\n\n");

  chestRow = 0;
  chestColumn = 1;
  chestValue = 11;
  chestRepeats = 13;
  chestHorizontal = false;

  placeChestTest(arr, chestRow, chestColumn, chestRepeats, chestValue,
                 chestHorizontal);

  printf("TEST: Overlap - there is already treasure here:\n\n");

  chestRow = 0;
  chestColumn = 0;
  chestValue = 11;
  chestRepeats = 8;
  chestHorizontal = false;

  placeChestTest(arr, chestRow, chestColumn, chestRepeats, chestValue,
                 chestHorizontal);

  printf("End of placeChest tests.\n");
}

// Deletes array from heap memory, assigns pointer to NULL
void cleanup(int *arr) {
  delete[] arr;
  arr = NULL;
}

int placeBronze(int *array, int row, int column, bool horizontal) {
  return placeChest(array, row, column, bronzeLength, bronzeNum, horizontal);
}

void consoleBronze(int *array) {
  int row = 0;
  int column = 0;
  bool horizontal = true;
  char alignment;
  char *name = "Bronze";
  int chestNum;
  int chestLength;
  printf("Placing %d cell long %s Chest\n...\nEnter 'h' to place the chest "
         "horizontally, or 'v' to place the chest vertically:",
         bronzeLength, name);
  scanf("%c", &alignment);
  while (alignment != 'h' && alignment != 'v') {
    printf("Horizontal or vertical? (h/v)\n");
    scanf("%c", &alignment);
    if (alignment == 'h') {
      horizontal = true;
    } else if (alignment == 'v') {
      horizontal = false;
    } else {
      printf("Error: invalid character\n");
    }
  }
  printf("Please enter a Row: ");
  scanf("%d", &row);
  while (row > maxRow || row < 0) {
    printf(
        "Error: index out or range. Please enter a number between 0 and %d\n",
        maxRow);
    scanf("%d", &row);
  }
  printf("Please enter a Column: ");
  scanf("%d", &column);
  while (column > maxColumn || column < 0) {
    printf(
        "Error: index out or range. Please enter a number between 0 and %d\n",
        maxColumn);
    printf("Please enter a Column: ");
    scanf("%d", &column);
  }
  if (placeChest(array, row, column, bronzeLength, bronzeNum, horizontal) ==
      -1) {
    printf("Something went wrong! Trying again\n...\n...\n...\n");
    consoleBronze(array);
  } else {
    printf("%s chest placed successfully!\n\n", name);
    printGrid(array);
  }
}

bool checkRange(int num, int max) {
  return num <= max && 0 <= num;
}

bool checkRow(int row, int rows) {
  if (checkRange(row, rows)) {
    return true;
  } else {
    printf("");
    return false;
  }
}



void consoleDig(int *array) {
  int row;
  int column;
  printf("Enter a coordinate to excavate\nRow: ");
  scanf("%d", &row);
  printf("Column: ");
  scanf("%d", &column);

  dig(array, row, column);
}
int main(int argc, char **argv) {
  // Hardcoded array

  int *arr = new int[cells]{0,  0,  -1,  0, 0, 0, 0,   -14, 0,  11, 11,  11, 11,
                            11, -1, -14, 0, 0, 0, 0,   0,   -1, 0,  -14, 13, 0,
                            -1, 0,  0,   0, 0, 0, -13, -1,  0,  -1, 12,  12, 12,
                            12, 13, 0,   0, 0, 0, 0,   0,   0,  0,  -1,  0,  0,
                            0,  0,  -1,  0, 0, 0, 15,  15,  0,  0,  0,   0};

  printGrid(arr);
  //  placeChestTestSuite(arr);
  //consoleBronze(arr);
  consoleDig(arr);

  // printGrid(arr);
  // show(arr);
  // reveal(arr);

  // // dig testing variables
  // int digRow = rows / 2;
  // int digColumn = columns / 3;
  // dig(arr, digRow, digColumn);

  // // digAll(arr, rows, columns); //uncomment to test dig on all cells
  cleanup(arr);
  return 0;
}
