#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL));

    char board[HEIGHT][WIDTH];
    SnakeNode* snake = initializeSnake();
    int score = 0;
    char lastMove = RIGHT;

    initializeBoard(board);
    board[snake->x][snake->y] = SNAKE;
    placeFruit(board);
    drawBoard(board);

    printf("Press any key to start...\n");
    while (!getInput());


    while (1) {
        char move = getInput();
        if (move != 0) lastMove = move;

        moveSnake(&snake, lastMove, board, &score);

        system("clear");

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (board[i][j] != WALL && board[i][j] != FRUIT) {
                    board[i][j] = EMPTY;
                }
            }
        }

        SnakeNode* current = snake;
        while (current != NULL) {
            board[current->x][current->y] = SNAKE;
            current = current->next;
        }

        drawBoard(board);
        printf("Score: %d\n", score);

        int speed = 1000000 - (score / 10) * 50000;
        if (speed < 100000) speed = 100000;

        usleep(speed);
    }

    free(snake);
    return 0;
}

