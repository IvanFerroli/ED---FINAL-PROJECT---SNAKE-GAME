#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL)); // Random seed

    char board[HEIGHT][WIDTH];
    SnakeNode* snake = initializeSnake(); // Create the snake
    int score = 0; // Declare score at the beginning
    char lastMove = RIGHT; // ✅ Start moving right by default

    initializeBoard(board);
    board[snake->x][snake->y] = SNAKE;
    placeFruit(board);
    drawBoard(board);

    while (1) {
        // ✅ Get user input, but default to lastMove if no input is given
        char move = getInput();
        if (move != 0) lastMove = move; // Only update if input was given

        moveSnake(&snake, lastMove, board, &score); // ✅ Move in last known direction

        system("clear"); // ✅ Clears the screen before drawing (Linux/macOS)
        // system("cls"); // ✅ Use this instead if you're on Windows

        // ✅ Instead of resetting the entire board, only update necessary positions
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (board[i][j] != WALL && board[i][j] != FRUIT) {
                    board[i][j] = EMPTY; // Clear only non-wall/non-fruit positions
                }
            }
        }

        // ✅ Draw the entire snake on the board
        SnakeNode* current = snake;
        while (current != NULL) {
            board[current->x][current->y] = SNAKE;
            current = current->next;
        }

        drawBoard(board); // ✅ Print updated board
        printf("Score: %d\n", score); // ✅ Print score after updating board

        usleep(500000); // ✅ Small delay (100ms) to smooth rendering and prevent flickering
    }

    free(snake);
    return 0;
}
