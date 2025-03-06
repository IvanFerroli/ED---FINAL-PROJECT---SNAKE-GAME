#ifndef GAME_H
#define GAME_H

#define WIDTH 10
#define HEIGHT 10

#define WALL '#'
#define EMPTY ' '
#define FRUIT 'O'
#define SNAKE 'S'

typedef struct SnakeNode {
    int x, y;
    struct SnakeNode* next;
} SnakeNode;

void initializeBoard(char board[HEIGHT][WIDTH]);
void drawBoard(char board[HEIGHT][WIDTH]);
void placeFruit(char board[HEIGHT][WIDTH]);
SnakeNode* initializeSnake();
char getInput();

#define UP 'W'
#define DOWN 'S'
#define LEFT 'A'
#define RIGHT 'D'

#define ARROW_UP 65
#define ARROW_DOWN 66
#define ARROW_RIGHT 67
#define ARROW_LEFT 68

void moveSnake(SnakeNode** head, char direction, char board[HEIGHT][WIDTH], int* score);

#endif
