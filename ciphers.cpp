#include <stdio.h>



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
