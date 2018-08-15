#include <stdio.h>

#include <stdlib.h>
#include <memory.h>
#include "battleships.h"

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
 * this function runs the rounds of the game in a loop until the game is over
 * @param gameBoard : the board of the game.
 */
void playGame(GameBoard *gameBoard)
{
    printf(START_GAME_MSG);
    int gameFlag = TRUE;
    while (gameFlag==TRUE)
    {
        gameFlag = playSingleRound(gameBoard);
    }
    if (gameFlag==WIN_GAME)
    {
        endGame(gameBoard);
        return;
    }
    if (gameFlag==EXIT_GAME)
    {
        freeGameBoard(gameBoard);
    }
}


/**
 * this function activates a single round in the game.
 * @param gameBoard : the game board
 * @return TRUE if the round finished as planed. EXIT_GAME if the user asked to exit the game
 */
int playSingleRound(GameBoard *gameBoard)
{
    printBoard(gameBoard);
    int row, col;
    int validMove = getMove(&row, &col, gameBoard);
    while (validMove==FALSE)
    {
        fprintf(stderr, INVALID_MOVE_MSG);
        validMove = getMove(&row, &col, gameBoard);
    }
    if (validMove==EXIT_GAME)
    {
        return EXIT_GAME;
    }
    return placeMove(row, col, gameBoard); // can return win game flag

}

/**
 * @brief this function terminates the game. prints game over and the final board.
 * @note here we use the free function for the allocation of the game board
 * @param gameBoard : the board of the game
 */
void endGame(GameBoard *gameBoard)
{
    printf(END_GAME_MSG);
    printBoard(gameBoard);
    freeGameBoard(gameBoard);
}

/**
 * this function prints the game board.
 * @param gameBoard : the game board
 */
void printBoard(GameBoard *gameBoard)
{
    char rowNum = 1;
    int colNum = 'a';
    int rowIndex, colIndex;
    printf(" ");
    for (rowIndex = 0 ; rowIndex < gameBoard->size ; ++rowIndex) // print the col numbers
    {
        printf(" %d", rowNum++);
    }
    printf("\n");
    for (rowIndex = 0 ; rowIndex < gameBoard->size ; ++rowIndex)
    {
        printf("%c", colNum++); // print the row numbers
        for (colIndex = 0 ; colIndex < gameBoard->size ; ++colIndex)
        { // print the status of the cell
            printf(" %c", gameBoard->board[rowIndex][colIndex].status);
        }
        printf("\n");
    }
}

/**
 * this function gets the move from the user and checks its validation.
 * @param row : the pointer for the row var that will set in the input value
 * @param column : the pointer for the col var that will set in the input value
 * @param gameBoard : the game board.
 * @return FALSE in case the input is not valid, TRUE for valid input, EXIT_GAME (-1) to exit
 */
int getMove(int *row, int *column, GameBoard *gameBoard)
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
    return isIndexInBoard(*row, *column, gameBoard->size); // checks if the index is valid
}

/**
 * this function free the memory allocated for the game board.
 * @param gameBoard : this is the board of the game.
 */
void freeGameBoard(GameBoard *gameBoard)
{
    int i;
    for (i = 0 ; i < gameBoard->size ; i++)
    {
        free(gameBoard->board[i]);
        gameBoard->board[i] = NULL;
    }
    free(gameBoard->board);
    gameBoard->board = NULL;
}


/**
 * the main function that runs the game.
 * @return 0 for a standard exit from the program, 1 for an exit because of an error in the program
 */
int main()
{
    GameBoard *gameBoard = (GameBoard *) malloc(sizeof(GameBoard));
    if (getSizeOfBoard(gameBoard)==FALSE)
    {
        fprintf(stderr, INVALID_SIZE_MSG);
        return 1;
    }

    if (buildGameBoard(gameBoard)==FALSE)
    { // the malloc failed
        fprintf(stderr, OUT_OF_MEMORY_MSG);
        return 1;
    }
    playGame(gameBoard);
    free(gameBoard);
    return 0;
}
