#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

const char HIT = 'x';
const char MISS = 'o';
const char INIT_CELL = '_';

const int sizeOfBoard = 10;
const int TRUE = 0;
const int FALSE = 1;


typedef struct Direction {
    int addToRow;
    int addToColumn;
} Direction;

Direction directions[4] = {
        {0,  1},
        {0,  -1},
        {1,  0},
        {-1, 0}
};

typedef struct Ship {
    char sign;
    int lenght;
    int numOfHits;
} Ship;

const Ship EMPTY = {'0', 0, 0};

typedef struct Cell {
    Ship content;
    char status;
} Cell;


/**
 * 'a' for aircraft carrier in length 5
 * 'p' for patrol in length 4
 * 'm' for Missile ship in length 3
 * 's' for submarine in length 3
 * 'd' for destroyer in length 2
 */
Ship gameShips[5] = {
        {'a', 5, 0},
        {'p', 4, 0},
        {'m', 3, 0},
        {'s', 3, 0},
        {'d', 2, 0},
};

/*
 * the game board
 */
Cell board[10][10];


void initBoard() {
    int i, j;
    for (i = 0; i < sizeOfBoard; ++i) {
        for (j = 0; j < sizeOfBoard; ++j) {
            board[i][j].status = INIT_CELL;
        }
    }
}

void initShipBoard() {
    int i, j;
    for (i = 0; i < sizeOfBoard; ++i) {
        for (j = 0; j < sizeOfBoard; ++j) {
            board[i][j].content = EMPTY;
        }
    }
}

int isCellFree(const int row, const int column) {
    if (board[row][column].content.sign == EMPTY.sign) {
        return TRUE;
    }
    return FALSE;
}

int isIndexInBoard(const int row, const int col) {
    if (row >= 0 && row < sizeOfBoard && col >= 0 && col < sizeOfBoard) {
        return TRUE;
    }
    return FALSE;
}

void getRandLocation(int *row, int *column, Direction *direction, int sizeOfShip) {
    int rowStart, colStart;
    do { // get the start location for the ship randomly
        rowStart = rand() % sizeOfBoard;
        colStart = rand() % sizeOfBoard;
    } while (isCellFree(rowStart, colStart) == FALSE);

    int rowFinish, colFinish;
    Direction curDirection;
    do { // get the direction for the ship to stand randomly
        curDirection = directions[rand() % 4]; // get a random direction
        rowFinish = rowStart + curDirection.addToRow * sizeOfShip;
        colFinish = colStart + curDirection.addToColumn * sizeOfShip;
    } while (isIndexInBoard(rowFinish, colFinish) == FALSE);
    // init the final values
    *row = rowStart;
    *column = colStart;
    *direction = curDirection;
}

int checkCollision(int row, int col, const Direction direction, int sizeOfShip) {
    int i;
    for (i = 0; i < sizeOfShip; ++i) {
        if (isCellFree(row, col) == FALSE) {
            return FALSE;
        }
        row += direction.addToRow;
        col += direction.addToColumn;
    }
    return TRUE;
}


void placeSingleShip(Ship ship) {
    int row, col, i;
    Direction direction;
    do {
        getRandLocation(&row, &col, &direction, ship.lenght); // find a location and direction
    } while (checkCollision(row, col, direction, ship.lenght) == FALSE); // check if the place is free

    for (i = 0; i < ship.lenght; ++i) { // now place the ship
        board[row][col].content = ship;
        row += direction.addToRow;
        col += direction.addToColumn;
    }
}

void placeShips() {
    initShipBoard();
    int i;
    for (i = 0; i < sizeof(gameShips) / sizeof(Ship); ++i) {
        placeSingleShip(gameShips[i]);
    }
}

int isLetter(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return TRUE;
    }
    return FALSE;
}

//TODO fix this!! its not working
void getMove(int *row, int *column) {
    printf("please make your move:\n");
    char rowInChar;
    int currCol;
    do {
        if (scanf("%c%d", &rowInChar, &currCol) == 2 && isLetter(rowInChar) == TRUE) {
            *row = rowInChar - 'a' + 1;
            *column = currCol;
            break;
        } else {
            fprintf(stderr, "Invalid move, try again\n");
        }
    } while (1);
}

void placeMove(const int row, const int column) {
    if (board[row][column].status != INIT_CELL) {
        printf("you already placed that move\n");
        return;
    }
    if (board[row][column].content.sign != EMPTY.sign) { // there is a ship part in this cell
        board[row][column].status = HIT;
        board[row][column].content.numOfHits++;

        printf("Hit!\n");
        return;
    }
    board[row][column].status = MISS; // the cell is empty
    printf("Miss :(\n");
}


void printBoard(Cell board[][10], int sizeOfBoard) {
    int rowIndex, colIndex;
    for (rowIndex = 0; rowIndex < sizeOfBoard; ++rowIndex) {
        for (colIndex = 0; colIndex < sizeOfBoard; ++colIndex) {
            printf(" %c", board[rowIndex][colIndex].status);
        }
        printf("\n");
    }
}

// TODO delete before final submission!!!!!!!
void printBehind(Cell board[][10], int sizeOfBoard) {
    int rowIndex, colIndex;
    for (rowIndex = 0; rowIndex < sizeOfBoard; ++rowIndex) {
        for (colIndex = 0; colIndex < sizeOfBoard; ++colIndex) {
            printf(" %c", board[rowIndex][colIndex].content.sign);
        }
        printf("\n");
    }
}


int isSunk(int row, int col) {
    Ship shipGotHit = board[row][col].content;
    if (shipGotHit.numOfHits == shipGotHit.lenght) {
        return TRUE;
    }
    return FALSE;
}

int main() {
    placeShips();
    printBehind(board, sizeOfBoard);

//    initBoard();
//    printBoard(board, 10);
//    int currRow;
//    int currColumn;
//
//    getMove(&currRow, &currColumn);
//    placeMove(currRow, currColumn);
//    printBoard(board, 10);
//    getMove(&currRow, &currColumn);
//    placeMove(currRow, currColumn);
//    printBoard(board, 10);
    return 0;
}