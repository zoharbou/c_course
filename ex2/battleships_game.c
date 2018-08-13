#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include "battleShips.h"

// -------------------------- const definitions -------------------------

/**
 * @var string massage
 * @brief error massage for the case that the input for the size the user entered is not valid
 */
const char *INVALID_SIZE_MSG = "the size you entered is not valid\n";

/**
 * @var string massage
 * @brief error massage for the case that the allocate of the memory failed.
 */
const char *OUT_OF_MEMORY_MSG = "fail to allocate memory\n";

/**
 * @var string massage
 * @brief error massage for the case that the move entered is not valid
 */
const char *INVALID_MOVE_MSG = "Invalid move, try again\n";

/**
 * @var string massage
 * @brief informative massage for asking the user for coordinates.
 */
const char *ENTER_MOVE_MSG = "enter coordinates: ";

/**
 * @var string massage
 * @brief informative massage for the case that we start a new game
 */
const char *START_GAME_MSG = "Ready to play\n";

/**
 * @var string massage
 * @brief informative massage for the case that the game is over
 */
const char *END_GAME_MSG = "Game over\n";

/**
 * @var constant for identify user input.
 * @brief if the user asks to exit the program before the game was finished it will write this word
 */
const char *EXIT_CALL = "exit";


// ------------------------------ functions -----------------------------

/**
 * this function adds a sunk ship to the counter to know how many ships are left in the game.
 * it checks if all the ship where sunk and if the answer is positive than it returns the value
 * to finish the game
 *@return TRUE for successful adding. WIN_GAME when add the ship sunk
 */
int addSunkShip(void)
{
    static int sunkShipCounter = 0;

    sunkShipCounter++;

    if (NUM_OF_GAME_SHIPS==sunkShipCounter)
    {
        return WIN_GAME;
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
    int gameFlag = TRUE;
    while (gameFlag==TRUE)
    {
        gameFlag = playSingleRound(sizeOfBoard);
    }
    if (gameFlag==WIN_GAME)
    {
        endGame(sizeOfBoard);
        return;
    }
    if (gameFlag == EXIT_GAME){
        freeGameBoard(sizeOfBoard);
    }
}


/**
 * this function activates a single round in the game.
 * @param sizeOfBoard : the size of the game board
 * @return TRUE if the round finished as planed. EXIT_GAME if the user asked to exit the game
 */
int playSingleRound(const int sizeOfBoard)
{
    printBoard(sizeOfBoard);
    int row, col;
    int validMove = getMove(&row, &col, sizeOfBoard);
    while (validMove==FALSE)
    {
        fprintf(stderr, INVALID_MOVE_MSG);
        validMove = getMove(&row, &col, sizeOfBoard);
    }
    if (validMove==EXIT_GAME)
    {
        return EXIT_GAME;
    }
    return placeMove(row, col); // can return win game flag

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
 * this function gets the move from the user and checks its validation.
 * @param row : the pointer for the row var that will set in the input value
 * @param column : the pointer for the col var that will set in the input value
 * @param sizeOfBoard : the size of the game board.
 * @return FALSE in case the input is not valid, TRUE for valid input, EXIT_GAME (-1) to exit
 */
int getMove(int *row, int *column, const int sizeOfBoard)
{
    printf(ENTER_MOVE_MSG);
    char inputRow[10];
    char inputCol[10];
    scanf("%s", inputRow);
    if (strcmp(inputRow, EXIT_CALL)==TRUE)
    { // we need to exit the program
        return EXIT_GAME;
    }
    if (strlen(inputRow)!=1)
    { // the input is not a single char
        return FALSE;
    }
    scanf("%s", inputCol); // get the col coordinate
    int currCol = atoi(inputCol);
    char rowInLetter = inputRow[0];
    if (isLetter(rowInLetter)==FALSE)
    { // the input is not a letter follows by a number.
        return FALSE;
    }
    *row = rowInLetter - 'a';
    *column = currCol - 1;
    return isIndexInBoard(*row, *column, sizeOfBoard); // checks if the index is valid
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
