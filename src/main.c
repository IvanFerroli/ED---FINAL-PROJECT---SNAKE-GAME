#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Random seed

    char board[HEIGHT][WIDTH];
    SnakeNode* snake = initializeSnake(); // Create the snake

    initializeBoard(board);  // Set up the board
    board[snake->x][snake->y] = SNAKE; // Place snake
    placeFruit(board); // Spawn the fruit
    drawBoard(board);  // Print the board

    // Read input (doesn't move yet)
    char move = getInput();
    printf("You pressed: %c\n", move);

    free(snake); // Clean memory
    return 0;
}
