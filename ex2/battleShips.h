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

// ------------------------------ includes ------------------------------

#ifndef EX2_BATTLESHIPS_H
#define EX2_BATTLESHIPS_H

// structs for the game
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
#define NUM_OF_GAME_SHIPS 5
#define EXIT_GAME (-1)
#define WIN_GAME 2

/**
 * @var a dynamic Cell 2d matrix
 *@brief the game board.
 */
//Cell **g_gameBoard;

// ------------------------------ function declarations -----------------------------

/**
 * @brief this function cleans the input field after we got the user input
 */
void buff_clr(void);

/**
 * this function checks the validity of the input size of the table. if its not valid it will
 * return FALSE (1), else TRUE (0).
 * @param sizeOfBoard: the input for the size of the table
 * @return 1 for invalidity 0 for validity.
 */
int isValidSize(const int sizeOfBoard);

/**
 * this function checks if a given coordinate is legal according to the size of the board.
 * @param row : the row index
 * @param col : the column index
 * @param sizeOfBoard : the size of the game board
 * @return TRUE for the case that the coordinate is valid. otherwise FALSE.
 */
int isIndexInBoard(const int row, const int col, const int sizeOfBoard);

/**
 * this function receives a coordinate and checks its matched Cell in the board is free to set a
 * ship in.
  * @param row : the row index
 * @param col : the column index
 * @param gameBoard : the board of the game
 * @return TRUE for the case that the coordinate is free. otherwise FALSE.
 */
int isCellFree(const int row, const int column, GameBoard *gameBoard);

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
int isCellValid(const int row, const int col, const int sizeOfShip, GameBoard *gameBoard);

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
                     GameBoard *gameBoard);

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
                   GameBoard *gameBoard);

/**
* this function places a single ship in a rand location on the board
* @param ship : the pointer for the ship we want to place
* @param gameBoard : the game board
*/
void placeSingleShip(Ship *ship, GameBoard *gameBoard);

/**
 * this function places all the ships in the game board in rand locations
 * @param gameBoard : a pointer to the game board
 */
void placeShips(GameBoard *gameBoard);

/**
 * this function init the game board for default values (the Cell's status to '_' and the Cell's
 * content to NULL) and places the ships in random locations.
 * @param gameBoard : the board of the game
 */
void initBoard(GameBoard *gameBoard);

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
 * this function receives a char and returns if its a small letter or not
 * @param ch : the char we want to check
 * @return TRUE if the char is a small english letter. otherwise FALSE.
 */
int isLetter(char ch);

/**
 * this function adds a sunk ship to the counter to know how many ships are left in the game.
 * it checks if all the ship where sunk and if the answer is positive than it returns the value
 * to finish the game
 *@return TRUE for successful adding. WIN_GAME when add the ship sunk
 */
int addSunkShip(void);

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
int isSunk(const int row, const int col, GameBoard *gameBoard);

/**
 *this function places the move that the user inserted. it prints to the screen the matched
 * massage according to the move that was made (already made, miss, hit, hit and sunk)
 * @param row : the index of the row for the move
 * @param column : the index of the column for the move
 * @param gameBoard : the board of the game
 * @return TRUE for successful move and WIN_GAME in case that the move finished the game
 */
int placeMove(const int row, const int column, GameBoard *gameBoard);

/**
 * this function prints the game board.
 * @param gameBoard : the game board
 */
void printBoard(GameBoard *gameBoard);

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

// -------------------------- const definitions -------------------------
