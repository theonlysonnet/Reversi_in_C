/**
* @file reversi.c
* @author <-- Your name here-->
* @brief This file is used for APS105 Lab 8. 2023W version
* @date 2023-03-14
*
*/
// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
#include "reversi.h"
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//int findIfLegal1(char board[][26], int dim, int x, int y, char colour);
int findLegalDir(char board[][26], int dim, int x, int y, char colour);
void makeAMove(char board[][26], int row, int col, char colour, int n, int deltaRow, int deltaCol);
int dirFlipCount(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void makeAMove(char board[][26], int row, int col, char colour, int n, int deltaRow, int deltaCol);
int flipCount(char board[][26], int dim, int x, int y, char colour);
bool checkWin(char board[][26], int n);
void whoWon(char board[][26], int n, char* winner);

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

//specially created variation of findiflegal that returns an int which can be broken down to figure out
//what directions are valid and make a move in all those directions
int findLegalDir(char board[][26], int dim, int x, int y, char colour) {
  int sum = 1;
  if (board[x][y] == 'B' || board[x][y] == 'W')
    return sum;
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

void makeAMove(char board[][26], int row, int col, char colour, int n, int deltaRow, int deltaCol) {
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

int dirFlipCount(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    char otherColour;
  if (colour == 'B') // sets other color based on color given
    otherColour = 'W';
  else
    otherColour = 'B';
  
  if (board[row + deltaRow][col + deltaCol] == 'U') {
    return 0;  //if first thing in specified direction is  empty it's auto false
  }

  int count = 1; //increment for checking each element in specified direction
  //while loop runs while the each subsequent element in direction is the other color
  while (positionInBounds(n, row + deltaRow*count, col + deltaCol*count) && board[row + deltaRow*count][col + deltaCol*count] == otherColour) {
    count++;  
  }

  if (count == 1)
    return 0; //if while loop does run cuz the first subsequent element isnt other color
  
  if (!positionInBounds(n, row + deltaRow*count, col + deltaCol*count)) {
    count--; 
  } //specific case for when the counting goes out of bounds (basically hard code)

  if (board[row + deltaRow*count][col + deltaCol*count] == 'U' || board[row + deltaRow*count][col + deltaCol*count] == otherColour)
    return 0; //if it went out of bounds and the last element is empty or other color return false
  else 
    return count;  //if nothing before occured then return true as the move is valid
}

int flipCount(char board[][26], int dim, int x, int y, char colour) {
  int sum = 0;
  int flips;

  flips = dirFlipCount(board, dim, x, y, colour, 0, 1);
  sum += flips;
  flips = dirFlipCount(board, dim, x, y, colour, 0, -1);
  sum += flips;
  flips = dirFlipCount(board, dim, x, y, colour, 1, 0);
  sum += flips;
  flips = dirFlipCount(board, dim, x, y, colour, -1, 0);
  sum += flips;
  flips = dirFlipCount(board, dim, x, y, colour, 1, 1);
  sum += flips;
  flips = dirFlipCount(board, dim, x, y, colour, -1, -1);
  sum += flips;
  flips = dirFlipCount(board, dim, x, y, colour, -1, 1);
  sum += flips;
  flips = dirFlipCount(board, dim, x, y, colour, 1, -1);
  sum += flips;

  return sum;
}

int makeMove(char board[26][26], int n, char turn, int *row, int *col) {
    int maxFlip = 0;
    int val;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            val = flipCount(board, n, x, y, turn);
            if (val > maxFlip && board[x][y] == 'U') {
                *row = x;
                *col = y;
                maxFlip = val;
            }
        }
    }
    return findLegalDir(board, n, *row, *col, turn);
}

bool checkWin(char board[][26], int n) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (board[x][y] == 'U') {
                if (findLegalDir(board, n, x, y, 'B') > 1 || findLegalDir(board, n, x, y, 'W') > 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

void whoWon(char board[][26], int n, char* winner) {
    int bCount = 0;
    int wCount = 0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (board[x][y] == 'B')
                bCount++;
            else if (board[x][y] == 'W')
                wCount++;
        }
    }
    if (bCount > wCount)
        *winner = 'B';
    else
        *winner = 'W';
}

//*******************************************************
// Note: Please only put your main function below
// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE

int main(void) {
// Write your own main function here
    // start of setting up of board
    int dim = 0;
    char compCol;
    char pColour;
    int turn = 0;

    printf("Enter the board dimension: ");
    scanf("%d", &dim);
    printf("Computer plays (B/W): ");
    scanf(" %c", &compCol);

    if (compCol == 'B') {
        pColour = 'W';
        turn = 0;
    }
    else {
        pColour = 'B';
        turn = 1;
    }

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

    char row, col;
    int iRow, iCol;
    int legalDir;
    bool win = true; //only for invalid move check
    //bool compCan = true;

    while (checkWin(board, dim) && win) {
        if (turn % 2 == 0) {
            legalDir = makeMove(board, dim, compCol, &iRow, &iCol);
            if (legalDir > 1) {
                //compCan = true;
                row = iRow +97;
                col = iCol +97;
                printf("Computer places %c at %c%c.\n", compCol, row, col);
                while (legalDir > 1) {
                    int dir = legalDir % 10;
                    legalDir /= 10;
                    if (dir == 1)
                        makeAMove(board, row-97, col-97, compCol, dim, 0, 1 );
                    else if (dir == 2)
                        makeAMove(board, row-97, col-97, compCol, dim, 0, -1 );
                    else if (dir == 3)
                        makeAMove(board, row-97, col-97, compCol, dim, 1, 0 );
                    else if (dir == 4)
                        makeAMove(board, row-97, col-97, compCol, dim, -1, 0 );
                    else if (dir == 5)
                        makeAMove(board, row-97, col-97, compCol, dim, 1, 1 );
                    else if (dir == 6)
                        makeAMove(board, row-97, col-97, compCol, dim, -1, -1 );
                    else if (dir == 7)
                        makeAMove(board, row-97, col-97, compCol, dim, -1, 1 );
                    else if (dir == 8)
                        makeAMove(board, row-97, col-97, compCol, dim, 1, -1 );
                }
                printBoard(board, dim);
            }
            else {
                printf("%c player has no valid move.\n", compCol);
                //compCan == false;
            }
            turn++;
        }
        else {
            printf("Enter move for colour %c (RowCol): ", pColour);
            scanf(" %c%c", &row, &col);
            legalDir = findLegalDir(board, dim, row-97, col-97, pColour);
            if ( positionInBounds(dim, row-97, col-97) && legalDir > 1) {
                while (legalDir > 1) {
                    int dir = legalDir % 10;
                    legalDir /= 10;
                    if (dir == 1)
                        makeAMove(board, row-97, col-97, pColour, dim, 0, 1 );
                    else if (dir == 2)
                        makeAMove(board, row-97, col-97, pColour, dim, 0, -1 );
                    else if (dir == 3)
                        makeAMove(board, row-97, col-97, pColour, dim, 1, 0 );
                    else if (dir == 4)
                        makeAMove(board, row-97, col-97, pColour, dim, -1, 0 );
                    else if (dir == 5)
                        makeAMove(board, row-97, col-97, pColour, dim, 1, 1 );
                    else if (dir == 6)
                        makeAMove(board, row-97, col-97, pColour, dim, -1, -1 );
                    else if (dir == 7)
                        makeAMove(board, row-97, col-97, pColour, dim, -1, 1 );
                    else if (dir == 8)
                        makeAMove(board, row-97, col-97, pColour, dim, 1, -1 );
                }
                printBoard(board, dim);
                turn++;
            }
            else {
                win = false; //if invalid move placed it breaks while
                printf("Invalid Move.\n");
                printf("%c player wins.", compCol);
            }
        }
    }
    if (win == true) {
        char winner;
        whoWon(board, dim, &winner);
        printf("%c player wins.", winner);
    }
    
    return 0;
}

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************