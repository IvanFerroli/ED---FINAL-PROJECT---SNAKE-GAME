#ifndef GAME_H
#define GAME_H

#define WIDTH 10
#define HEIGHT 10

// Symbols
#define WALL '#'
#define EMPTY ' '
#define FRUIT 'O'
#define SNAKE 'S'

// Snake structure (linked list)
typedef struct SnakeNode {
    int x, y;
    struct SnakeNode* next;
} SnakeNode;

// Function declarations
void initializeBoard(char board[HEIGHT][WIDTH]);
void drawBoard(char board[HEIGHT][WIDTH]);
void placeFruit(char board[HEIGHT][WIDTH]);
SnakeNode* initializeSnake();

#endif
