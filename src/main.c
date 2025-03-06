#include "game.h"

int main() {
    char board[HEIGHT][WIDTH];

    initializeBoard(board); // Set up the board
    drawBoard(board);       // Print the board

    return 0;
}
