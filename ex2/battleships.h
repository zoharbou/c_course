/**
 * @file battleship.h
 * @author  Zohar Bouchnik <zohar.bouchnik@mail.huji.ac.il>
 * @version 1.0
 * @date 15 august 2018
 *
 * @brief this is the header file of the program. here you can find the declarations of some of
 * the functions in the program. the program runs the battle ship game.
 * a guessing game for two players (one is the computer) on which the computer places a fleet of ships
 * (including battleships). The locations of the fleets are concealed from the other player.
 * the player "shots" at the other player's ships (the computer's ships),
 * and the objective of the game is to destroy the opposing player's fleet.
 *the game is over when all the ships sunk
 *
 * @section LICENSE
 * none
 *
 * @section DESCRIPTION
 *
 * Input  : a board size and moves
 * Process: playing the battleship game
 * Output : the game will stop if the user win or if the user writes "exit" in the command line
 */


// -------------------------- const definitions -------------------------

#ifndef EX2_BATTLESHIPS_H
#define EX2_BATTLESHIPS_H

/**
 * @brief this struct is a direction struct. if you add it to the coordinate you move one step to
 * the direction initialized in it. (can be right, left, up, down...)
 * @addToRow the num you need to add to the row coordinate to move to the wanted direction
 * @addToColumn the num you need to add to the column coordinate to move to the wanted direction
 */
typedef struct Direction
{
    int addToRow;
    int addToColumn;
} Direction;


/**
 * @brief this is a ship structure. all the instruments in the game are from that type.
 * @length the length of the ship (how many cells it catches on the board
 * @numOfHits the number of hits the user made on that ship. init with zero first
 */

typedef struct Ship
{
    int length;
    int numOfHits;
} Ship;


/**
 * the board is made with cells. each one has a coordinate on the board.
 * @content a pointer for the content of the cell- it can be a ship or null. init with null please
 * @status the status of the cell in the game board- hit (x), miss (o) or not reached yet(_).
 */
typedef struct Cell
{
    Ship *content;
    char status;
} Cell;


/**
 * the game board struct. it contains a dynamic array of the board and its size
 * (num of rows,columns is equal)
 */
typedef struct GameBoard
{
    Cell **board;
    int size;
} GameBoard;


/**
 * constants for true and false conditions. mostly for readability of the code.
 */
#define TRUE 0
#define FALSE 1

/**
 * the flags for exit and winning
 */
#define EXIT_GAME (-1)
#define WIN_GAME 2



// ------------------------------ function declarations -----------------------------


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
void getRandLocation(int *row, int *column, Direction *direction, int sizeOfShip,
                     GameBoard *gameBoard);


/**
 * this function places all the ships in the game board in rand locations
 * @param gameBoard : a pointer to the game board
 */
void placeShips(GameBoard *gameBoard);


/**
 * this function builds the game board according to the given size. locates the ships and sets it
 * for a new game. (uses malloc! the free function is separated, please pay attention)
 * @param gameBoard : a pointer to the game board that the function is going to build
 * @return FALSE in case the malloc can't allocate memory for the board, TRUE otherwise
 */
int buildGameBoard(GameBoard *gameBoard);

/**
 * this function free the memory allocated for the game board.
 * @param gameBoard : this is the board of the game.
 */
void freeGameBoard(GameBoard *gameBoard);


/**
 * this function gets the move from the user and checks its validation.
 * @param row : the pointer for the row var that will set in the input value
 * @param column : the pointer for the col var that will set in the input value
 * @param gameBoard : the game board.
 * @return FALSE in case the input is not valid, TRUE otherwise
 */
int getMove(int *row, int *column, GameBoard *gameBoard);

/**
 * this function checks if the ship that just got hit sunk also. we get its coordinates.
 * @param row : the index of the row
 * @param col : the index of the col
 * @param gameBoard : the board of the game
 * @return TRUE if the ship is sunk, FALSE otherwise. returns WIN_GAME if all the ship where sunk
 */
int isSunk(int row, int col, GameBoard *gameBoard);

/**
 *this function places the move that the user inserted. it prints to the screen the matched
 * massage according to the move that was made (already made, miss, hit, hit and sunk)
 * @param row : the index of the row for the move
 * @param column : the index of the column for the move
 * @param gameBoard : the board of the game
 * @return TRUE for successful move and WIN_GAME in case that the move finished the game
 */
int placeMove(int row, int column, GameBoard *gameBoard);

/**
 * this function prints the game board.
 * @param gameBoard : the game board
 */
void printBoard(const GameBoard *gameBoard);

/**
 * this function activates a single round in the game.
 * @param gameBoard : the game board
 * @return TRUE if the round finished as planed. EXIT_GAME if the user asked to exit the game
 */
int playSingleRound(GameBoard *gameBoard);

/**
 * @brief this function terminates the game. prints game over and the final board.
 * @note here we use the free function for the allocation of the game board
 * @param gameBoard : the board of the game
 */
void endGame(GameBoard *gameBoard);

/**
 * this function checks if a given coordinate is legal according to the size of the board.
 * @param row : the row index
 * @param col : the column index
 * @param sizeOfBoard : the size of the game board
 * @return TRUE for the case that the coordinate is valid. otherwise FALSE.
 */
int isIndexInBoard(int row, int col, int sizeOfBoard);

/**
 * this function gets the size of the board from the user
 * @param gameBoard : a pointer to the game board
 * @return TRUE if the size is valid and FALSE otherwise
 */
int getSizeOfBoard(GameBoard *gameBoard);

/**
 * this function runs the rounds of the game in a loop until the game is over
 * @param gameBoard : the board of the game.
 */
void playGame(GameBoard *gameBoard);


#endif //EX2_BATTLESHIPS_H
