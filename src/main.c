#include "game.h"
#include <stdlib.h>
#include <time.h> // Include for time()

int main() {
    srand(time(NULL)); // ✅ Initialize RNG once

    char board[HEIGHT][WIDTH];
    SnakeNode* snake = initializeSnake(); // Create the snake

    initializeBoard(board);  // Set up the board
    board[snake->x][snake->y] = SNAKE; // Place snake head
    placeFruit(board); // Spawn the fruit randomly
    drawBoard(board);  // Print the board

    free(snake); // Clean memory
    return 0;
}
