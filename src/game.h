#ifndef GAME_H
#define GAME_H

// Board dimensions
#define WIDTH 10
#define HEIGHT 10

// Symbols
#define WALL '#'
#define EMPTY ' '
#define FRUIT 'O'
#define SNAKE 'S'

// Function declarations
void initializeBoard(char board[HEIGHT][WIDTH]);
void drawBoard(char board[HEIGHT][WIDTH]);

#endif
