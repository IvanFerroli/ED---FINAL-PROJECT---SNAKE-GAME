#include <stdio.h>
#include <stdlib.h>
#include "game.h"


// Initialize the game board
void initializeBoard(char board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                board[i][j] = WALL;  // Place walls on the borders
            } else {
                board[i][j] = EMPTY; // Empty space inside
            }
        }
    }
}

// Initialize the snake in the center of the board
SnakeNode* initializeSnake() {
    SnakeNode* head = (SnakeNode*)malloc(sizeof(SnakeNode));
    head->x = HEIGHT / 2;
    head->y = WIDTH / 2;
    head->next = NULL; // Only one segment for now
    return head;
}

// Print the game board
void drawBoard(char board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
