// ------------------------------ includes ------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
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
 * @var a dynamic Cell 2d matrix
 *@brief the game board.
 */
Cell **g_gameBoard;

/**
 * @var informative flag
 * @brief will turn to const true (0) when the game is over. init with const false (1).
 */
static int gameOverFlag = 1; // init with false


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
 * @return TRUE for the case that the coordinate is free. otherwise FALSE.
 */
int isCellFree(const int row, const int column)
{
    if (g_gameBoard[row][column].content==NULL)
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
 * @param sizeOfBoard : the size of the game board
 * @return TRUE for the case that the coordinate is valid. otherwise FALSE.
 */
int isCellValid(const int row, const int col, const int sizeOfShip, const int sizeOfBoard)
{
    int i, rowFinish, colFinish;
    for (i = 0 ; i < sizeof(directions) / sizeof(Direction) ; ++i)
    { // go throw all the directions and check each one
        rowFinish = row + directions[i].addToRow * (sizeOfShip - 1);
        colFinish = col + directions[i].addToColumn * (sizeOfShip - 1);
        if (isIndexInBoard(rowFinish, colFinish, sizeOfBoard)==TRUE)
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
 * @param sizeOfBoard : the size of the game board
 */
void getRandLocation(int *row, int *column, Direction *direction, const int sizeOfShip,
                     const int sizeOfBoard)
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
 * @return TRUE for the case that there are no collisions and FALSE otherwise.
 */
int checkCollision(int row, int col, const Direction direction, const int sizeOfShip)
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

/**
 * this function places a single ship in a rand location on the board
 * @param ship : the pointer for the ship we want to place
 * @param sizeOfBoard : the size of the board
 */
void placeSingleShip(Ship *ship, const int sizeOfBoard)
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

/**
 * this function places all the ships in the game board in rand locations
 * @param sizeOfBoard : the size of the game board
 */
void placeShips(const int sizeOfBoard)
{
    int i;
    for (i = 0 ; i < sizeof(gameShips) / sizeof(Ship) ; ++i)
    {
        placeSingleShip(&gameShips[i], sizeOfBoard);
    }
}

/**
 * this function init the game board for default values (the Cell's status to '_' and the Cell's
 * content to NULL) and places the ships in random locations.
 * @param sizeOfBoard : the size of the game board
 */
void initBoard(const int sizeOfBoard)
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

/**
 * this function builds the game board according to the given size. locates the ships and sets it
 * for a new game. (uses malloc! the free function is separated, please pay attention)
 * @param sizeOfBoard : the size of the board
 * @return FALSE in case the malloc can't allocate memory for the board, TRUE otherwise
 */
int buildGameBoard(const int sizeOfBoard)
{
    int i;
    g_gameBoard = (Cell **) malloc((sizeOfBoard) * sizeof(Cell *));
    if (g_gameBoard==NULL)
    { // out of memory
        return FALSE;
    }
    for (i = 0 ; i < sizeOfBoard ; i++)
    {
        g_gameBoard[i] = (Cell *) malloc((sizeOfBoard) * sizeof(Cell));
        if (g_gameBoard[i]==NULL)
        { // out of memory
            return FALSE;
        }
    }
    initBoard(sizeOfBoard);
    return TRUE;
}

/**
 * this function free the memory allocated for the game board.
 * @param sizeOfBoard : the size of the board
 */
void freeGameBoard(const int sizeOfBoard)
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
 * this function adds a sunk ship to the counter to know how many ships are left in the game.
 * it checks if all the ship where sunk and if the answer is positive than it finishes the game
 */
void addSunkShip(void)
{
    static int sunkShipCounter = 0;

    sunkShipCounter++;

    if (sizeof(gameShips) / sizeof(Ship)==sunkShipCounter)
    {
        gameOverFlag = TRUE;
    }
}

/**
 * this function gets the move from the user and checks its validation.
 * @param row : the pointer for the row var that will set in the input value
 * @param column : the pointer for the col var that will set in the input value
 * @param sizeOfBoard : the size of the game board.
 * @return FALSE in case the input is not valid, TRUE otherwise
 */
int getMove(int *row, int *column, const int sizeOfBoard)
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

/**
 * this function checks if the ship that just got hit sunk also. we get its coordinates.
 * @param row : the index of the row
 * @param col : the index of the col
 * @return TRUE if the ship is sunk, FALSE otherwise
 */
int isSunk(const int row, const int col)
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

/**
 *this function places the move that the user inserted. it prints to the screen the matched
 * massage according to the move that was made (already made, miss, hit, hit and sunk)
 * @param row : the index of the row for the move
 * @param column : the index of the column for the move
 */
void placeMove(const int row, const int column)
{
    if (g_gameBoard[row][column].status!=INIT_CELL)
    { // the move was already made
        printf(REPEATED_MOVE_MSG);
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

/**
 * this function prints the game board.
 * @param sizeOfBoard : the size of the game board
 */
void printBoard(const int sizeOfBoard)
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


/**
 * this function activates a single round in the game.
 * @param sizeOfBoard : the size of the game board
 */
void playSingleRound(const int sizeOfBoard)
{
    printBoard(sizeOfBoard);
    int row, col;
    while (getMove(&row, &col, sizeOfBoard)==FALSE)
    {
        fprintf(stderr, INVALID_MOVE_MSG);
    }
    if (gameOverFlag==FALSE) // if the game is over no need to make tha move
    {
        placeMove(row, col);
    }
}

/**
 * @brief this function terminates the game. prints game over and the final board.
 * @note here we use the free function for the allocation of the game board
 * @param sizeOfBoard
 */
void endGame(const int sizeOfBoard)
{
    printf(END_GAME_MSG);
    printBoard(sizeOfBoard);
    freeGameBoard(sizeOfBoard);
}

/**
 * this function gets the size of the board from the user
 * @param sizeOfBoard : the pointer for the size of the board. here we set the size
 * @return TRUE if the size is valid and FALSE otherwise
 */
int getSizeOfBoard(int *sizeOfBoard)
{
    printf(ENTER_SIZE_MSG);
    if (scanf("%d", sizeOfBoard)!=1)
    {
        return FALSE;
    }
    buff_clr();
    if (isValidSize(*sizeOfBoard)==FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

/**
 * this function runs the rounds of the game in a loop until the game is over
 * @param sizeOfBoard : the size of the board
 */
void playGame(const int sizeOfBoard)
{
    printf(START_GAME_MSG);
    while (gameOverFlag==FALSE)
    {
        playSingleRound(sizeOfBoard);
    }
    endGame(sizeOfBoard);
}

/**
 * the main function that runs the game.
 * @return 0 for a standard exit from the program, 1 for an exit because of an error in the program
 */
int main()
{
    int sizeOfBoard;
    if (getSizeOfBoard(&sizeOfBoard)==FALSE)
    {
        fprintf(stderr, INVALID_SIZE_MSG);
        return 1;
    }
    if (buildGameBoard(sizeOfBoard)==FALSE)
    { // the malloc failed
        fprintf(stderr, OUT_OF_MEMORY_MSG);
        return 1;
    }
    playGame(sizeOfBoard);
    return 0;
}