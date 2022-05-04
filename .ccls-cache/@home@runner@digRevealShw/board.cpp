#include <stdio.h>

enum Cipher {
SHOW, REVEAL, NONE
};

class Board {
public:
int rows;
int columns;
int *data;

Board(int setRows, int setColumns) {
  rows = setRows;
  columns = setColumns;
  data = new int[rows * columns];
}
bool onBoard(int row, int column) {
  return row < rows && column < columns;
}
bool validateCell(int row, int column) {
  if (onBoard(row, column)) {
    if (data[row * columns + column] == 0) {
      return true;
    }
  }
  return false;
}

bool modifyCell(int row, int column, int value) {
  if (validateCell(row, column)) {
    data[(row * columns) + column] = value;
    return true;
  }
  return false;
}
void simpleModify(int row, int column, int value) {
  if (validateCell(row, column)){
    data[row * columns + column] = value;
    printBoard(); 
  }
  
}

void gridMover(int *row, int *column, bool horizontal) {
  if (horizontal) {
    column++;
  } else {
    row++;
  }
}

bool validateRange(int row, int column, int length, bool horizontal) {
  for (int cell = 0; cell < length; cell++) {
    if (!validateCell(row, column)) {
      return false;
    }

  }
  return true;
}

bool modifyRange(int row, int column, int length, bool horizontal, int value) {
  if (validateRange(row, column, length, horizontal)) {
    for (int cell = 0; cell < length; cell++) {
      modifyCell(row, column, value);
      if (horizontal) {
        column++;
      } else {
        row++;
      }
    }
  }
  return true;
}


void printBoard() {
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      printf("[%3d]", data[row * columns + column]);
    }
    printf("\n");
  }
  printf("\n");
}

char showCipher(int cell) {
  char c;
  if (cell > -1) {
    c = '-';
  } else if (cell == -1) {
    c = 'X';
  } else {
    c = '@';
  }
  return c;
}

char revealCipher(int cell) {
  char c;
  switch(cell) {
    case -1:
      c = 'X';
    break;
    case 0:
      c = '-';
    break;
    case 11:
      c = 'a';
    break;
    case 12:
      c = 'b';
    break;
    case 13:
      c = 'c';
    break;
    case 14:
      c = 'd';
    break;
    case 15:
      c = 'e';
    break;
    case -11:
      c = 'A';
    break;
    case -12:
      c = 'B';
    break;
    case -13:
      c = 'C';
    break;
    case -14:
      c = 'D';
    break;
    case -15:
      c = 'E';
    break;
  }
  return c;
}
void printCipher(Cipher cipher) {
    for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      char c;
      int cell = data[(row * columns) + column];
      switch(cipher) {
        case SHOW:
        printf("[%3c]", showCipher(cell));
        break;
        case REVEAL:
        printf("[%3c]", revealCipher(cell));
        break;
        case NONE:
        printf("[%3d]", cell);
        break;
      }
    }
    printf("\n");
  }
  printf("\n");
}
};

