#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "board.cpp"

using std::string;

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
enum TreasureType {
BRONZE, SILVER, GOLD, RUBIES, VIBRANIUM
};
class TreasureChest {
public: 
TreasureType type;
int length;
int cipher;
string name;
TreasureChest(TreasureType type) {
  switch(type) {
    case BRONZE:
      length = bronzeLength;
      cipher = bronzeNum;
      name = "Bronze";
    break;
    case SILVER:
      length = silverLength;
      cipher = silverNum;
      name = "Silver";
    break;
    case GOLD:
      length = goldLength;
        cipher = goldNum;
      name = "Gold";
    break;
    case RUBIES:
      length = rubiesLength;
      cipher = rubiesNum;
      name = "Rubies";
    break;
    case VIBRANIUM:
      length = vibraniumLength;
      cipher = vibraniumNum;
    break;
    
  }
}
};

TreasureType typeChar(char c) {
  TreasureType type;
  switch(c) {
    case 'b':
    type = BRONZE;
    break;
    case 's':
    type = SILVER;
    break;
    case 'g':
    type = GOLD;
    break;
    case 'r':
    type = RUBIES;
    break;
    case 'v':
    type = VIBRANIUM;
  }
  return type;
}

void freeBuffer() {
    int c;
while((c = getchar()) != '\n' && c != EOF);
}

bool hideTreasure(int row, int column, bool horizontal, TreasureChest chest, Board board) {
  return board.modifyRange(row, column, chest.length, horizontal, chest.cipher);
}

bool align() {
  char alignment;
  printf("Would you like to hide your treasure horizontally or vertically?\n");
  printf("h/v\n");
  //Buffer overflow fixed - logic is murky

  scanf("%c", &alignment);
  freeBuffer();
  
  if (alignment == 'h') {
    return true;
  } else if (alignment == 'v') {
    return false;
  } else {
    return align();
  }
}

int userRow() {
  int row;
  printf("Row:");
  scanf("%d", &row);
  freeBuffer();
  if (row < 0 || row >= rows) {
    printf("ERROR");
    return userRow();
  } else {
    return row;
  }
}

int userColumn() {
  int column;
  printf("Column:");
  scanf("%d", &column);
  freeBuffer();
  if (column < 0 || column >= columns) {
    printf("ERROR");
    return userColumn();
  } else {
    return column;
  }
}

void userHideTreasure(TreasureType treasure, Board *board) {

  TreasureChest *chest = new TreasureChest(treasure);
  int row;
  int column;
  bool horizontal;
  system("clear");
  board->printBoard();

  printf("Hiding %s chest. Occupies %d cells.\n",chest->name.c_str(), chest->length);

  horizontal = align();
  row = userRow();
  column = userColumn();
  bool ret = board->modifyRange(row, column, chest->length, horizontal, chest->cipher);
  if (!ret) {
       userHideTreasure(treasure, board); 
  }

  system("clear");
  board->printBoard();
  

}

void userHideAll(Board *board) {
  for (int i = 0; i < 5; i++) {
    userHideTreasure((TreasureType)i, board);
  }
}

void game() {
  Board *selfBoard = new Board(rows, columns);
  Board *aiBoard = new Board(rows, columns);
  //Print welcom

  //Prompt user chest placement
}


int main(int argc, char **argv) {
  Board *board = new Board(rows, columns);
//userHideTreasure(BRONZE, board);
  userHideAll(board);

  return 0;
}
