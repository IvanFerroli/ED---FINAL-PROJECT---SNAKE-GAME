#include "game.h"
#include <stdlib.h>

int main() {
    char board[HEIGHT][WIDTH];
    SnakeNode* snake = initializeSnake(); // Create the snake

    initializeBoard(board);  // Set up the board
    board[snake->x][snake->y] = SNAKE; // Place snake head
    drawBoard(board);        // Print the board

    free(snake); // Clean memory
    return 0;
}
