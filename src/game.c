#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <ctype.h> 
#include <sys/select.h>
#include <unistd.h>
#include <termios.h> 
#include <fcntl.h>     

void initializeBoard(char board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                board[i][j] = WALL;
            } else {
                board[i][j] = EMPTY;
            }
        }
    }
}

SnakeNode* initializeSnake() {
    SnakeNode* head = (SnakeNode*)malloc(sizeof(SnakeNode));
    head->x = HEIGHT / 2;
    head->y = WIDTH / 2;
    head->next = NULL;
    return head;
}

void drawBoard(char board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void placeFruit(char board[HEIGHT][WIDTH]) {
    int x, y;
    do {
        x = rand() % (HEIGHT - 2) + 1;
        y = rand() % (WIDTH - 2) + 1;
    } while (board[x][y] != EMPTY);
    board[x][y] = FRUIT;
}

char getInput() {
    struct termios oldt, newt;
    char input = 0;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    input = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if (input == '\033') {
        getchar();
        switch (getchar()) {
            case ARROW_UP: return UP;
            case ARROW_DOWN: return DOWN;
            case ARROW_RIGHT: return RIGHT;
            case ARROW_LEFT: return LEFT;
        }
    }
    return (input != EOF) ? toupper(input) : 0;
}

void moveSnake(SnakeNode** head, char direction, char board[HEIGHT][WIDTH], int* score) {
    int newX = (*head)->x;
    int newY = (*head)->y;

    switch (direction) {
        case UP: newX--; break;
        case DOWN: newX++; break;
        case LEFT: newY--; break;
        case RIGHT: newY++; break;
        default: return;
    }

    if (board[newX][newY] == WALL || board[newX][newY] == SNAKE) {
        exit(0);
    }

    int fruitEaten = (board[newX][newY] == FRUIT);
    if (fruitEaten) {
        *score += 10;
        placeFruit(board);
    }

    SnakeNode* newHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    newHead->x = newX;
    newHead->y = newY;
    newHead->next = *head;
    *head = newHead;

    if (!fruitEaten) {
        SnakeNode* temp = *head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        board[temp->next->x][temp->next->y] = EMPTY;
        free(temp->next);
        temp->next = NULL;
    }

    SnakeNode* current = *head;
    while (current != NULL) {
        board[current->x][current->y] = SNAKE;
        current = current->next;
    }
}
