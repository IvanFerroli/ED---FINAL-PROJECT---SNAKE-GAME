#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <ctype.h> // ✅ Include this at the top of game.c


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

// Place a fruit at a random empty position
void placeFruit(char board[HEIGHT][WIDTH]) {
    int x, y;

    do {
        x = rand() % (HEIGHT - 2) + 1;  // Avoid walls
        y = rand() % (WIDTH - 2) + 1;
    } while (board[x][y] != EMPTY); // Ensure empty space

    board[x][y] = FRUIT;
}

// Read user input (WASD)
char getInput() {
    char input;
    printf("Enter move (WASD): ");
    input = getchar();
    while (getchar() != '\n'); // Clear input buffer
    return toupper(input); // ✅ Converts 'w' -> 'W', 'a' -> 'A', etc.
}



// Move the snake in the given direction
void moveSnake(SnakeNode** head, char direction, char board[HEIGHT][WIDTH], int* score) {
    int newX = (*head)->x;
    int newY = (*head)->y;

    // Determine new head position
    switch (direction) {
        case UP: newX--; break;
        case DOWN: newX++; break;
        case LEFT: newY--; break;
        case RIGHT: newY++; break;
        default: return; // Invalid input, ignore
    }

    printf("DEBUG: Moving from (%d, %d) to (%d, %d)\n", (*head)->x, (*head)->y, newX, newY);

    // Check for collision
    if (board[newX][newY] == WALL) {
        printf("Game Over! You hit a wall.\n");
        exit(0);
    }
    if (board[newX][newY] == SNAKE) {
        printf("Game Over! You hit yourself.\n");
        exit(0);
    }

    // Check if fruit was eaten
    int fruitEaten = (board[newX][newY] == FRUIT);
    if (fruitEaten) {
        *score += 10;  // ✅ Increase score
        placeFruit(board); // Generate new fruit
    }

    // Add new head
    SnakeNode* newHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    newHead->x = newX;
    newHead->y = newY;
    newHead->next = *head;
    *head = newHead;

    // ✅ FIX: Remove tail only if fruit was NOT eaten
    if (!fruitEaten) {
        SnakeNode* temp = *head;
        while (temp->next->next != NULL) { // Find second last node
            temp = temp->next;
        }
        board[temp->next->x][temp->next->y] = EMPTY; // Clear old tail position
        free(temp->next); // Remove tail
        temp->next = NULL;
    }

    // ✅ FIX: Ensure board updates for all snake parts
    SnakeNode* current = *head;
    while (current != NULL) {
        board[current->x][current->y] = SNAKE;
        current = current->next;
    }
}
