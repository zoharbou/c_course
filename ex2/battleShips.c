// ------------------------------ includes ------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <assert.h>


/**
 * @file
 * @author  Zohar Bouchnik <zohar.bouchnik@mail.huji.ac.il>
 * @version 1.0
 * @date 01 oct 2018
 *
 * @brief
 *
 * @section LICENSE
 * none
 *
 * @section DESCRIPTION
 *
 * Input  :
 * Process:
 * Output :
 */


// -------------------------- const definitions -------------------------

typedef struct Direction
{
    int addToRow;
    int addToColumn;
} Direction;

Direction directions[4] = {
        {0,  1},
        {0,  -1},
        {1,  0},
        {-1, 0}
};

typedef struct Ship
{
    char signature;
    int length;
    int numOfHits;
} Ship;


const Ship EMPTY = {'0', 0, 0};

typedef struct Cell
{
    Ship *content;
    char status;
} Cell;


/**
 * the number of arguments expected
 */
const int EXPECTED_ARGS = 2;

/**
 * error massage for the case that the user enters a wrong num of arguments
 */
const char *INVALID_INPUT_MSG = "One argument expected.\n";

/**
 * error massage for the case that the input for the size the user entered is not valid
 */
const char *INVALID_SIZE_MSG = "the size you entered is not valid\n";

const char *ALREADY_HIT_MSG = "Already been hit.\n";
const char *MISS_MSG = "Miss.\n";
const char *HIT_MSG = "Hit!\n";
const char *SUNK_MSG = "Hit and Sunk.\n";
const char *INVALID_MOVE_MSG = "Invalid move, try again\n";
const char *ENTER_MOVE_MSG = "enter coordinates: ";
const char *ENTER_SIZE_MSG = "enter board size: ";
const char *START_GAME_MSG = "Ready to play\n";
const char *END_GAME_MSG = "Game over\n";

Cell **g_gameBoard;


const char HIT = 'x';
const char MISS = 'o';
const char INIT_CELL = '_';
const char *EXIT_CALL = "exit";

const int TRUE = 0;
const int FALSE = 1;

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

static int gameOverFlag = 1; // init with false

/**
 * @var
 *@brief
 */


// ------------------------------ function declarations -----------------------------


// ------------------------------ functions -----------------------------

void buff_clr(void)
{
    char junk;
    do
    {
        junk = (char) getchar();
    } while (junk!='\n');
}


/**
 * this function checks the validity of the input size of the table. if its not valid it will
 * return 1, else 0.
 * @param size the input for the size of the table
 * @return 1 for invalidity 0 for validity.
 */
int isValidSize(const int sizeOfBoard)
{
    if (sizeOfBoard < 5 || sizeOfBoard > 26)
    {
        return FALSE;
    }
    return TRUE;
}

int isIndexInBoard(const int row, const int col, int sizeOfBoard)
{
    if (row >= 0 && row < sizeOfBoard && col >= 0 && col < sizeOfBoard)
    {
        return TRUE;
    }
    return FALSE;
}

int isCellFree(const int row, const int column)
{
    if (g_gameBoard[row][column].content==NULL)
    {
        return TRUE;
    }
    return FALSE;
}

int isCellValid(int row, int col, int sizeOfShip, int sizeOfBoard)
{
    int i, rowFinish, colFinish;
    for (i = 0 ; i < sizeof(directions) / sizeof(Direction) ; ++i)
    {
        rowFinish = row + directions[i].addToRow * (sizeOfShip - 1);
        colFinish = col + directions[i].addToColumn * (sizeOfShip - 1);
        if (isIndexInBoard(rowFinish, colFinish, sizeOfBoard)==TRUE)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void getRandLocation(int *row, int *column, Direction *direction, int sizeOfShip, int sizeOfBoard)
{
    int rowStart, colStart;
    do
    { // get the start location for the ship randomly
        rowStart = rand() % sizeOfBoard;
        colStart = rand() % sizeOfBoard;
    } while (isCellFree(rowStart, colStart)==FALSE || isCellValid(rowStart, colStart, sizeOfShip,
                                                                  sizeOfBoard)==FALSE);

    int rowFinish, colFinish;
    Direction curDirection;
    do
    { // get the direction for the ship to stand randomly
        curDirection = directions[rand() % 4]; // get a random direction
        rowFinish = rowStart + curDirection.addToRow * (sizeOfShip - 1);
        colFinish = colStart + curDirection.addToColumn * (sizeOfShip - 1);
    } while (isIndexInBoard(rowFinish, colFinish, sizeOfBoard)==FALSE);
    // init the final values
    *row = rowStart;
    *column = colStart;
    *direction = curDirection;
}

int checkCollision(int row, int col, const Direction direction, int sizeOfShip)
{
    int i;
    for (i = 0 ; i < sizeOfShip ; ++i)
    {
        if (isCellFree(row, col)==FALSE)
        {
            return FALSE;
        }
        row += direction.addToRow;
        col += direction.addToColumn;
    }
    return TRUE;
}

void placeSingleShip(Ship *ship, int sizeOfBoard)
{
    int row, col, i;
    Direction direction;
    do
    {
        getRandLocation(&row, &col, &direction, ship->length,
                        sizeOfBoard); // find a location and direction
    } while (checkCollision(row, col, direction, ship->length)==FALSE); // check if the place is
    // free

    for (i = 0 ; i < ship->length ; ++i)
    { // now place the ship
        g_gameBoard[row][col].content = ship;
        row += direction.addToRow;
        col += direction.addToColumn;
    }
}

void placeShips(int sizeOfBoard)
{
    int i;
    for (i = 0 ; i < sizeof(gameShips) / sizeof(Ship) ; ++i)
    {
        placeSingleShip(&gameShips[i], sizeOfBoard);
    }
}

void initBoard(int sizeOfBoard)
{
    int i, j;
    for (i = 0 ; i < sizeOfBoard ; ++i)
    {
        for (j = 0 ; j < sizeOfBoard ; ++j)
        {
            g_gameBoard[i][j].status = INIT_CELL;
            g_gameBoard[i][j].content = NULL;

        }
    }
    placeShips(sizeOfBoard); // placing the ships on the board.
}

void buildGameBoard(int sizeOfBoard)
{
    int i;
    g_gameBoard = (Cell **) malloc((sizeOfBoard) * sizeof(Cell *));
    for (i = 0 ; i < sizeOfBoard ; i++)
    {
        g_gameBoard[i] = (Cell *) malloc((sizeOfBoard) * sizeof(Cell));
    }
    initBoard(sizeOfBoard);
}

void freeGameBoard(int sizeOfBoard)
{
    int i;
    for (i = 0 ; i < sizeOfBoard ; i++)
    {
        free(g_gameBoard[i]);
        g_gameBoard[i] = NULL;
    }
    free(g_gameBoard);
    g_gameBoard = NULL;
}

int isLetter(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return TRUE;
    }
    return FALSE;
}


void addSunkShip()
{
    static int sunkShipCounter = 0;

    sunkShipCounter++;

    if (sizeof(gameShips) / sizeof(Ship)==sunkShipCounter)
    {
        gameOverFlag = TRUE;
    }
}

//TODO fix this!! its not working
int getMove(int *row, int *column, int sizeOfBoard)
{
    printf(ENTER_MOVE_MSG);
    char inputStr[10];
    int inputNum;
    scanf("%s %d", inputStr, &inputNum);
    buff_clr();
    if (strcmp(inputStr, EXIT_CALL)==TRUE)
    { // we need to exit the program
        gameOverFlag = TRUE;
        return TRUE;
    }
    if (strlen(inputStr)!=1)
    { // the input is not a single char
        return FALSE;
    }

    char rowInLetter = inputStr[0];
    if (isLetter(rowInLetter)==FALSE)
    { // the input is not a letter follows by a number.
        return FALSE;
    }
    *row = rowInLetter - 'a';
    *column = inputNum - 1;
    return isIndexInBoard(*row, *column, sizeOfBoard); // checks if the index is valid
}

int isSunk(int row, int col)
{
    Ship *shipGotHit = g_gameBoard[row][col].content;
    assert(shipGotHit!=NULL);
    if (shipGotHit->numOfHits==shipGotHit->length)
    {
        addSunkShip();
        return TRUE;
    }
    return FALSE;
}

void placeMove(const int row, const int column)
{
    if (g_gameBoard[row][column].status!=INIT_CELL)
    { // the move was already made
        printf(ALREADY_HIT_MSG);
        return;
    } // its a new move
    if (g_gameBoard[row][column].content!=NULL)
    { // there is a ship part in this cell
        g_gameBoard[row][column].status = HIT; // in the user moves board
        g_gameBoard[row][column].content->numOfHits++; // adding a hit to the ship
        if (isSunk(row, column)==TRUE)
        { // the ship was sunk after the last move
            printf(SUNK_MSG);
            return;
        }
        printf(HIT_MSG); // just a hit no sunk
        return;
    } // the cell is empty
    g_gameBoard[row][column].status = MISS;
    printf(MISS_MSG);
}


void printBoard(int sizeOfBoard)
{
    char rowNum = 1;
    int colNum = 'a';
    int rowIndex, colIndex;
    printf(" ");
    for (rowIndex = 0 ; rowIndex < sizeOfBoard ; ++rowIndex) // print the col numbers
    {
        printf(" %d", rowNum++);
    }
    printf("\n");
    for (rowIndex = 0 ; rowIndex < sizeOfBoard ; ++rowIndex)
    {
        printf("%c", colNum++); // print the row numbers
        for (colIndex = 0 ; colIndex < sizeOfBoard ; ++colIndex)
        { // print the status of the cell
            printf(" %c", g_gameBoard[rowIndex][colIndex].status);
        }
        printf("\n");
    }
}


void playSingleRound(int sizeOfBoard)
{
    printBoard(sizeOfBoard);
    int row, col;
    while (getMove(&row, &col, sizeOfBoard)==FALSE)
    {
        fprintf(stderr, INVALID_MOVE_MSG);
    }
    if (gameOverFlag==FALSE)
    {
        placeMove(row, col);
    }
}

void endGame(int sizeOfBoard)
{
    printf(END_GAME_MSG);
    printBoard(sizeOfBoard);
    freeGameBoard(sizeOfBoard);
}

int main()
{
    int size;
    printf(ENTER_SIZE_MSG);
    scanf("%d", &size);
    buff_clr();
    if (isValidSize(size)==FALSE)
    {
        fprintf(stderr, INVALID_SIZE_MSG);
        return 0;
    }
    buildGameBoard(size);
    printf(START_GAME_MSG);
    while (gameOverFlag==FALSE)
    {
        playSingleRound(size);
    }
    endGame(size);
    return 0;
}