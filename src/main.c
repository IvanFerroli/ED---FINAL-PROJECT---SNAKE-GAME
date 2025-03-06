#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Random seed

    char board[HEIGHT][WIDTH];
    SnakeNode* snake = initializeSnake(); // Create the snake

    initializeBoard(board);
    board[snake->x][snake->y] = SNAKE; // ✅ This needs to update after movement
    placeFruit(board);
    drawBoard(board);

    while (1) {
        char move = getInput();
        printf("DEBUG: Player pressed: %c\n", move); // Debugging print
    
        moveSnake(&snake, move, board);
    
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
    
        drawBoard(board); // Print updated board
    }
    
    

    free(snake);
    return 0;
}


