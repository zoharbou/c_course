// ------------------------------ includes ------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "battleShips.h"

/**
 * @file battleShips.c
 * @author  Zohar Bouchnik <zohar.bouchnik@mail.huji.ac.il>
 * @version 1.0
 * @date 12 august 2018
 *
 * @brief this is the implementation file for the battleShips game.
 * strategy for the game and logic idea
 *
 * @section LICENSE
 * none
 *
 * @section DESCRIPTION
 * this is the implementation file for the battleShips game.
 * strategy for the game and logic idea
 * Input  :
 * Process: implementation for the functions in the header file
 * Output :
 */


// -------------------------- const definitions -------------------------



/**
 * @var string massage
 * @brief informative massage for the case that the input coordinates was already chosen.
 */
const char *REPEATED_MOVE_MSG = "you already placed that move.\n";

/**
 * @var string massage
 * @brief informative massage for the case that the user didn't hit any ship.
 */
const char *MISS_MSG = "Miss.\n";

/**
 * @var string massage
 * @brief informative massage for the case that the user hit a ship
 */
const char *HIT_MSG = "Hit!\n";

/**
 * @var string massage
 * @brief informative massage for the case that the user sunk a ship
 */
const char *SUNK_MSG = "Hit and Sunk.\n";


/**
 * @var string massage
 * @brief informative massage to ask the user for a board size
 */
const char *ENTER_SIZE_MSG = "enter board size: ";


/**
 * an array of directions for the game. right left up and down
 */
Direction directions[4] = {
        {0,  1}, // right
        {0,  -1}, // left
        {1,  0}, // up
        {-1, 0} // down
};

/**
 * @brief an array of the game ships:
 * aircraft carrier in length 5
 * patrol in length 4
 * Missile ship in length 3
 * submarine in length 3
 * destroyer in length 2
 */
Ship gameShips[5] = {
        {5, 0},
        {4, 0},
        {3, 0},
        {3, 0},
        {2, 0},
};

/**
 * the upper and lower bounds for the game board.
 */
const int MIN_SIZE = 5;
const int MAX_SIZE = 26;

/**
 * the lowest index possible for the game board. maximal is simply the board size - 1.
 * maximal cant be constant cause its unknown at compile time
 */
const int MIN_INDEX = 0;

/**
 * @brief constants for the Cell status. possible stages are- miss, hit, unreached.
 */

const char HIT = 'x';
const char MISS = 'o';
const char INIT_CELL = '_';



// ------------------------------ functions -----------------------------

/**
 * @brief this function cleans the input field after we got the user input
 */
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
 * return FALSE (1), else TRUE (0).
 * @param sizeOfBoard: the input for the size of the table
 * @return 1 for invalidity 0 for validity.
 */
int isValidSize(const int sizeOfBoard)
{
    if (sizeOfBoard < MIN_SIZE || sizeOfBoard > MAX_SIZE)
    {
        return FALSE;
    }
    return TRUE;
}

/**
 * this function checks if a given coordinate is legal according to the size of the board.
 * @param row : the row index
 * @param col : the column index
 * @param sizeOfBoard : the size of the game board
 * @return TRUE for the case that the coordinate is valid. otherwise FALSE.
 */
int isIndexInBoard(const int row, const int col, const int sizeOfBoard)
{
    if (row >= MIN_INDEX && row < sizeOfBoard && col >= MIN_INDEX && col < sizeOfBoard)
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * this function receives a coordinate and checks its matched Cell in the board is free to set a
 * ship in.
  * @param row : the row index
 * @param col : the column index
 * @param gameBoard : the board of the game
 * @return TRUE for the case that the coordinate is free. otherwise FALSE.
 */
int isCellFree(const int row, const int column, GameBoard *gameBoard)
{
    if (gameBoard->board[row][column].content==NULL)
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * this function checks if the Cell in the given coordinate is valid in the way that the ship we
 * want to init in it can start from this coordinate and be placed in any of the directions
 * possible in the game. if its not possible to place it in any of the directions we return FALSE.
 * otherwise it means the coordinate is a possible start point for that ship (just in terms of
 * board limits)
 * @param row : the row index
 * @param col : the column index
 * @param sizeOfShip : the size of the ship we want to place
 * @param gameBoard : the game board
 * @return TRUE for the case that the coordinate is valid. otherwise FALSE.
 */
int isCellValid(const int row, const int col, const int sizeOfShip, GameBoard *gameBoard)
{
    int i, rowFinish, colFinish;
    for (i = 0 ; i < sizeof(directions) / sizeof(Direction) ; ++i)
    { // go throw all the directions and check each one
        rowFinish = row + directions[i].addToRow * (sizeOfShip - 1);
        colFinish = col + directions[i].addToColumn * (sizeOfShip - 1);
        if (isIndexInBoard(rowFinish, colFinish, gameBoard->size)==TRUE)
        { // we fount a valid direction so the coordinate is ok
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * this function uses the rand function to find a start coordinate and a valid direction for
 * the ship size. it tries until a full success
 * @param row : a pointer for the row index. the final row index will be writen to the value of
 * the pointer.
 * @param col : a pointer for the column index. the final col index will be writen to the value of
 * the pointer.
 * @param direction : the pointer for the direction. the final direction chosen will set in that
 * pointer value.
 * @param sizeOfShip : the size of the ship we want to locate
 * @param gameBoard : the game board
 */
void getRandLocation(int *row, int *column, Direction *direction, const int sizeOfShip,
                     GameBoard *gameBoard)
{
    int rowStart, colStart;
    do
    { // get the start location for the ship randomly
        rowStart = rand() % gameBoard->size;
        colStart = rand() % gameBoard->size;
    } while (isCellFree(rowStart, colStart, gameBoard)==FALSE ||
             isCellValid(rowStart, colStart, sizeOfShip, gameBoard)==FALSE);

    int rowFinish, colFinish;
    Direction curDirection;
    do
    { // get the direction for the ship to stand randomly
        curDirection = directions[rand() % 4]; // get a random direction
        rowFinish = rowStart + curDirection.addToRow * (sizeOfShip - 1);
        colFinish = colStart + curDirection.addToColumn * (sizeOfShip - 1);
    } while (isIndexInBoard(rowFinish, colFinish, gameBoard->size)==FALSE);
    // set the final values
    *row = rowStart;
    *column = colStart;
    *direction = curDirection;
}

/**
 * this function checks for collisions with other ships in the board. if is returns TRUE it means
 * the location and direction are valid and free from any collision. otherwise it will return FALSE
 * @param row : the start index for the row coordinate for the ship to stand
 * @param col : the start index for the column coordinate for the ship to stand
 * @param direction : the chosen direction of the ship we want to check
 * @param sizeOfShip : the size of the ship we want to locate on the board
 * @param gameBoard : the board of the game
 * @return TRUE for the case that there are no collisions and FALSE otherwise.
 */
int checkCollision(int row, int col, const Direction direction, const int sizeOfShip,
                   GameBoard *gameBoard)
{
    int i;
    for (i = 0 ; i < sizeOfShip ; ++i)
    {
        if (isCellFree(row, col, gameBoard)==FALSE)
        {
            return FALSE;
        }
        row += direction.addToRow;
        col += direction.addToColumn;
    }
    return TRUE;
}

/**
 * this function places a single ship in a rand location on the board
 * @param ship : the pointer for the ship we want to place
 * @param gameBoard : the game board
 */
void placeSingleShip(Ship *ship, GameBoard *gameBoard)
{
    int row, col, i;
    Direction direction;
    do
    {
        // find a location and direction
        getRandLocation(&row, &col, &direction, ship->length, gameBoard);
        // check if the place is free
    } while (checkCollision(row, col, direction, ship->length, gameBoard)==FALSE);

    for (i = 0 ; i < ship->length ; ++i)
    { // now place the ship
        gameBoard->board[row][col].content = ship;
        row += direction.addToRow;
        col += direction.addToColumn;
    }
}

/**
 * this function places all the ships in the game board in rand locations
 * @param gameBoard : a pointer to the game board
 */
void placeShips(GameBoard *gameBoard)
{
    int i;
    for (i = 0 ; i < sizeof(gameShips) / sizeof(Ship) ; ++i)
    {
        placeSingleShip(&gameShips[i], gameBoard);
    }
}

/**
 * this function init the game board for default values (the Cell's status to '_' and the Cell's
 * content to NULL) and places the ships in random locations.
 * @param gameBoard : the board of the game
 */
void initBoard(GameBoard *gameBoard)
{
    int i, j;
    for (i = 0 ; i < gameBoard->size ; ++i)
    {
        for (j = 0 ; j < gameBoard->size ; ++j)
        {
            gameBoard->board[i][j].status = INIT_CELL;
            gameBoard->board[i][j].content = NULL;

        }
    }
    placeShips(gameBoard); // placing the ships on the board.
}

/**
 * this function builds the game board according to the given size. locates the ships and sets it
 * for a new game. (uses malloc! the free function is separated, please pay attention)
 * @param gameBoard : a pointer to the game board that the function is going to build
 * @return FALSE in case the malloc can't allocate memory for the board, TRUE otherwise
 */
int buildGameBoard(GameBoard *gameBoard)
{
    int i;
    gameBoard->board = (Cell **) malloc((gameBoard->size) * sizeof(Cell *));
    if (*gameBoard->board==NULL)
    { // out of memory
        return FALSE;
    }
    for (i = 0 ; i < gameBoard->size ; i++)
    {
        gameBoard->board[i] = (Cell *) malloc((gameBoard->size) * sizeof(Cell));
        if (gameBoard->board[i]==NULL)
        { // out of memory
            return FALSE;
        }
    }
    initBoard(gameBoard);
    return TRUE;
}


/**
 * this function receives a char and returns if its a small letter or not
 * @param ch : the char we want to check
 * @return TRUE if the char is a small english letter. otherwise FALSE.
 */
int isLetter(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return TRUE;
    }
    return FALSE;
}


/**
 * this function checks if the ship that just got hit sunk also. we get its coordinates.
 * @param row : the index of the row
 * @param col : the index of the col
 * @param gameBoard : the board of the game
 * @return TRUE if the ship is sunk, FALSE otherwise. returns WIN_GAME if all the ship where sunk
 */
int isSunk(const int row, const int col, GameBoard *gameBoard)
{
    Ship *shipGotHit = gameBoard->board[row][col].content;
    assert(shipGotHit!=NULL);
    if (shipGotHit->numOfHits==shipGotHit->length)
    {
        return addSunkShip(); // WIN_GAME or TRUE
    }
    return FALSE;
}

/**
 *this function places the move that the user inserted. it prints to the screen the matched
 * massage according to the move that was made (already made, miss, hit, hit and sunk)
 * @param row : the index of the row for the move
 * @param column : the index of the column for the move
 * @param gameBoard : the board of the game
 * @return TRUE for successful move and WIN_GAME in case that the move finished the game
 */
int placeMove(const int row, const int column, GameBoard *gameBoard)
{
    if (gameBoard->board[row][column].status!=INIT_CELL)
    { // the move was already made
        printf(REPEATED_MOVE_MSG);
        return TRUE;
    } // its a new move
    if (gameBoard->board[row][column].content!=NULL)
    { // there is a ship part in this cell
        gameBoard->board[row][column].status = HIT; // in the user moves board
        gameBoard->board[row][column].content->numOfHits++; // adding a hit to the ship
        int sunkFlag = isSunk(row, column, gameBoard);
        if (sunkFlag==WIN_GAME)
        { // the ship was sunk after the last move and the user won the game
            return WIN_GAME;
        }
        if (sunkFlag==TRUE) // sunk but there are ships left in the game
        {
            printf(SUNK_MSG);
            return TRUE;
        }
        printf(HIT_MSG); // just a hit no sunk
        return TRUE;
    } // the cell is empty
    gameBoard->board[row][column].status = MISS;
    printf(MISS_MSG);
    return TRUE;
}


/**
 * this function gets the size of the board from the user
 * @param gameBoard : a pointer to the game board
 * @return TRUE if the size is valid and FALSE otherwise
 */
int getSizeOfBoard(GameBoard *gameBoard)
{
    printf(ENTER_SIZE_MSG);
    int sizeOfBoard;
    if (scanf("%d", &sizeOfBoard)!=1)
    {
        return FALSE;
    }
    buff_clr();
    if (isValidSize(sizeOfBoard)==FALSE)
    {
        return FALSE;
    }
    gameBoard->size = sizeOfBoard;
    return TRUE;
}

