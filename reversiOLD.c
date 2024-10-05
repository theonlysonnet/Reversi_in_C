//
// Author: Sonnet Salice
//

#include "reversi.h"
//#include <stdbool.h>
#include <stdio.h>
//#include <stdlib.h>

int findIfLegal1(char board[][26], int dim, int x, int y, char colour);
int findIfLegal(char board[][26], int dim, int x, int y, char colour);
void makeMove(char board[][26], int row, int col, char colour, int n, int deltaRow, int deltaCol);

void printBoard(char board[][26], int n) {
  printf("  ");
  for (int x = 97; x < 97 + n; x++) {  //remember 97 is ASCII for 'a'
    printf("%c", x);
  } 
  int c = 97;
  printf("\n");
  for (int x = 0; x < n; x++) {
    printf("%c ", c);
    for (int y = 0; y < n; y++) {
      printf("%c", board[x][y]);
    }
    c++;
    printf("\n");
  }

}

bool positionInBounds(int n, int row, int col) {
  return (row < n && row >= 0 && col < n && col >= 0);
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  char otherColour;
  if (colour == 'B') // sets other color based on color given
    otherColour = 'W';
  else
    otherColour = 'B';
  
  if (board[row + deltaRow][col + deltaCol] == 'U') {
    return false;  //if first thing in specified direction is  empty it's auto false
  }

  int count = 1; //increment for checking each element in specified direction
  //while loop runs while the each subsequent element in direction is the other color
  while (positionInBounds(n, row + deltaRow*count, col + deltaCol*count) && board[row + deltaRow*count][col + deltaCol*count] == otherColour) {
    count++;  
  }

  if (count == 1)
    return false; //if while loop does run cuz the first subsequent element isnt other color
  
  if (!positionInBounds(n, row + deltaRow*count, col + deltaCol*count)) {
    count--; 
  } //specific case for when the counting goes out of bounds (basically hard code)

  if (board[row + deltaRow*count][col + deltaCol*count] == 'U' || board[row + deltaRow*count][col + deltaCol*count] == otherColour)
    return false; //if it went out of bounds and the last element is empty or other color return false
  else 
    return true;  //if nothing before occured then return true as the move is valid
}

//first variation of findiflegal that tells if ANY direction is valid
int findIfLegal1(char board[][26], int dim, int x, int y, char colour) {
  if (checkLegalInDirection(board, dim, x, y, colour, 0, 1)) {
    return 1;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, 0, -1)) {
    return 2;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, 1, 0)) {
    return 3;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, -1, 0)) {
    return 4;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, 1, 1)) {
    return 5;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, -1, -1)) {
    return 6;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, -1, 1)) {
    return 7;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, 1, -1)) {
    return 8;
  }
  
  return 0;
}

//specially created variation of findiflegal that returns an int which can be broken down to figure out
//what directions are valid and make a move in all those directions
int findIfLegal(char board[][26], int dim, int x, int y, char colour) {
  int sum = 1;
  if (checkLegalInDirection(board, dim, x, y, colour, 0, 1)) {
    sum *= 10;
    sum += 1;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, 0, -1)) {
    sum *= 10;
    sum += 2;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, 1, 0)) {
    sum *= 10;
    sum += 3;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, -1, 0)) {
    sum *= 10;
    sum += 4;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, 1, 1)) {
    sum *= 10;
    sum += 5;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, -1, -1)) {
    sum *= 10;
    sum += 6;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, -1, 1)) {
    sum *= 10;
    sum += 7;
  }
  if (checkLegalInDirection(board, dim, x, y, colour, 1, -1)) {
    sum *= 10;
    sum += 8;
  }
  
  return sum;
}

void makeMove(char board[][26], int row, int col, char colour, int n, int deltaRow, int deltaCol) {
  //makes move in specified direction
  char otherColour;
  if (colour == 'B')
    otherColour = 'W';
  else
    otherColour = 'B';
  board[row][col] = colour;
  int count = 1;
  while (positionInBounds(n, row + deltaRow*count, col + deltaCol*count) && board[row + deltaRow*count][col + deltaCol*count] == otherColour) {
    board[row + deltaRow*count][col + deltaCol*count] = colour; //while in bounds and elements are other color it switches
    count++;
  }
}

int main(void) {
  // start of setting up of board
  int dim = 0;
  printf("Enter the board dimension: ");
  scanf("%d", &dim);
  char board[26][26];
  for (int x = 0; x < 26; x++) {
    for (int y = 0; y < 26; y++) {
      board[x][y] = 'U';
    }
  }
  board[dim/2-1][dim/2-1] = 'W';
  board[dim/2][dim/2-1] = 'B';
  board[dim/2-1][dim/2] = 'B';
  board[dim/2][dim/2] = 'W';
  //initializing of board complete

  printBoard(board, dim); //print initial 

  char color = 'a', row = 'a', col = 'a';
  printf("Enter board configuration:");
  while (color != '!' && row !='!' && col != '!') { //entering of configurations till !!!
    scanf(" %c%c%c", &color, &row, &col);
    if (color != '!' && row !='!' && col != '!') {
      board[(int)(row-'a')][(int)(col - 'a')] = color;
    }
  }
  printf("\n");
  printBoard(board,dim); //print post applying 

  printf("Available moves for W:\n");
  for (int x = 0; x < dim; x++) {
    for (int y = 0; y < dim; y++) {
      if (board[x][y] == 'U' && findIfLegal1(board, dim, x, y, 'W') > 0) { //there's two variations of findIfLegal
        printf("%c%c\n", x + 97, y + 97);
      }
    }
  }

  printf("Available moves for B:\n");
  for (int x = 0; x < dim; x++) {
    for (int y = 0; y < dim; y++) {
      if (board[x][y] == 'U' && findIfLegal1(board, dim, x, y, 'B') > 0) { //there's two variations of findIfLegal
        printf("%c%c\n", x + 97, y + 97);
      }
    }
  }

  char colo, rowe, colum;
  printf("Enter a move:");  //user input move
  scanf(" %c%c%c", &colo, &rowe, &colum);
  
  printf("\n");
  if (positionInBounds(dim, rowe-97, colum-97) && findIfLegal1(board, dim, rowe-97, colum-97, colo) > 0) { //first variation of findIfLegal
    printf("Valid move.\n");
    int sum = findIfLegal(board, dim, rowe-97, colum-97, colo);  
    //specially created variation of findiflegal that returns an int which can be broken down to figure out
    //what directions are valid and make a move in all those directions
    while (sum > 1) {
      int dir = sum%10;
      sum /= 10;
      if (dir == 1)
      makeMove(board, rowe-97, colum-97, colo, dim, 0, 1 );
      else if (dir == 2)
        makeMove(board, rowe-97, colum-97, colo, dim, 0, -1 );
      else if (dir == 3)
        makeMove(board, rowe-97, colum-97, colo, dim, 1, 0 );
      else if (dir == 4)
        makeMove(board, rowe-97, colum-97, colo, dim, -1, 0 );
      else if (dir == 5)
        makeMove(board, rowe-97, colum-97, colo, dim, 1, 1 );
      else if (dir == 6)
        makeMove(board, rowe-97, colum-97, colo, dim, -1, -1 );
      else if (dir == 7)
        makeMove(board, rowe-97, colum-97, colo, dim, -1, 1 );
      else if (dir == 8)
        makeMove(board, rowe-97, colum-97, colo, dim, 1, -1 );
    }
    printBoard(board, dim);
  }
  else {
    printf("Invalid move.\n");
    printBoard(board, dim);
  }

  return 0;
}
