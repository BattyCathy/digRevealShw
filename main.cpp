#include <stdio.h>

//Austin Roach
//CS 151




int flatten(int row, int column, int columns) {
  return (row * columns) + column;
}

void printGrid(int rows, int columns, int* grid) {
  printf("Printing Grid: \n");
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      int cellNum = flatten(row, column, columns);
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

void show(int *arr, int rows, int columns) {
  printf("Show Method: \n0 is '-' \n-1 is 'X' \nOther negatives are '@' \nPositives are '-'\n");
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      int cellNumber = flatten(row, column, columns);
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

void reveal(int *arr, int rows, int columns) {
  printf("Reveal Method:\n0 is '-'\n-1 is 'X'\n11-15 are letters 'a-e' respectively\n-(11 - 15) are letters 'A-E' respectively\n");
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      int cellNumber = flatten(row, column, columns);
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
      }  else if (cell == 11) {
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

void dig(int *arr, int row, int rows, int column, int columns) {
      printf("Dig Method:\nModifies our array\nIf the cell was 0, it is now -1\nIf the cell was positive, it is now negative\nModifying Column #%d, Row #%d\n", column, row);
  int coord = flatten(row, column, columns);
  
  if (arr[coord] == 0) {
    arr[coord] = -1;
  } if (arr[coord] > 0) {
    arr[coord] *= -1;
  }
  printGrid(rows, columns, arr);
}

void digAll(int *arr, int rows, int columns) {
  
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      dig(arr, row, rows, column, columns);
    }
    
  }

}




int main(int argc, char** argv) {

  int rows = 8;
  int columns = 8;
  int cells = rows * columns;

  int digRow = rows / 2;
  int digColumn = columns / 3;

  int *arr = new int[cells]{0,0,-1,0,0,0,0,-14,
0,11,11,11,11,11,-1,-14,
0,0,0,0,0,-1,0,-14,
13,0,-1,0,0,0,0,0,
-13,-1,0,-1,12,12,12,12,
13,0,0,0,0,0,0,0,
0,-1,0,0,0,0,-1,0,
0,0,15,15,0,0,0,0};

  printGrid(rows, columns, arr);
  show(arr, rows, columns);
  reveal(arr, rows, columns);
  dig(arr, digRow, rows, digColumn, columns);
  // digAll(arr, rows, columns); //uncomment to test dig on all cells
  delete[]arr;
  arr = NULL;

  return 0;
}

