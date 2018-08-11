#include <stdio.h>

 char board[10][10] = {
        '0','0','0','0','0','x','0','0','0','0',
        '0','0','0','0','0','x','0','0','0','0',
        '0','0','0','0','0','x','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0'
};

void printBoard(char board[][10], int sizeOfBoard) {
    int rowIndex, colIndex;
    for (rowIndex = 0; rowIndex < sizeOfBoard; ++rowIndex) {
        for (colIndex = 0; colIndex < sizeOfBoard; ++colIndex) {
            printf(" %c", board[rowIndex][colIndex]);
        }
        printf("\n");
    }
}

int main() {
    printBoard(board, 10);
    return 0;
}