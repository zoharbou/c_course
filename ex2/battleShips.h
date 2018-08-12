
#ifndef EX2_BATTLESHIPS_H
#define EX2_BATTLESHIPS_H

#endif //EX2_BATTLESHIPS_H

// -------------------------- const definitions -------------------------

/**
 * @var string massage
 * @brief error massage for the case that the input for the size the user entered is not valid
 */
const char *INVALID_SIZE_MSG = "the size you entered is not valid\n";

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
 * @brief informative massage to ask the user for a board size
 */
const char *ENTER_SIZE_MSG = "enter board size: ";

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
 * @var string massage
 * @brief error massage for the case that the allocate of the memory failed.
 */
const char *OUT_OF_MEMORY_MSG = "fail to allocate memory\n";
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
 * an array of directions for the game. right left up and down
 */
Direction directions[4] = {
        {0,  1}, // right
        {0,  -1}, // left
        {1,  0}, // up
        {-1, 0} // down
};

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
 * @brief constants for the Cell status. possible stages are- miss, hit, unreached.
 */

const char HIT = 'x';
const char MISS = 'o';
const char INIT_CELL = '_';

/**
 * @var constant for identify user input.
 * @brief if the user asks to exit the program before the game was finished it will write this word
 */
const char *EXIT_CALL = "exit";

/**
 * constants for true and false conditions. mostly for readability of the code.
 */
const int TRUE = 0;
const int FALSE = 1;

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
 * @return TRUE for the case that the coordinate is free. otherwise FALSE.
 */
int isCellFree(const int row, const int column);

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
int isCellValid(const int row, const int col, const int sizeOfShip, const int sizeOfBoard);

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
                     const int sizeOfBoard);

/**
 * this function checks for collisions with other ships in the board. if is returns TRUE it means
 * the location and direction are valid and free from any collision. otherwise it will return FALSE
 * @param row : the start index for the row coordinate for the ship to stand
 * @param col : the start index for the column coordinate for the ship to stand
 * @param direction : the chosen direction of the ship we want to check
 * @param sizeOfShip : the size of the ship we want to locate on the board
 * @return TRUE for the case that there are no collisions and FALSE otherwise.
 */
int checkCollision(int row, int col, const Direction direction, const int sizeOfShip);

/**
 * this function places a single ship in a rand location on the board
 * @param ship : the pointer for the ship we want to place
 * @param sizeOfBoard : the size of the board
 */
void placeSingleShip(Ship *ship, const int sizeOfBoard);

/**
 * this function places all the ships in the game board in rand locations
 * @param sizeOfBoard : the size of the game board
 */
void placeShips(const int sizeOfBoard);

/**
 * this function init the game board for default values (the Cell's status to '_' and the Cell's
 * content to NULL) and places the ships in random locations.
 * @param sizeOfBoard : the size of the game board
 */
void initBoard(const int sizeOfBoard);

/**
 * this function builds the game board according to the given size. locates the ships and sets it
 * for a new game. (uses malloc! the free function is separated, please pay attention)
 * @param sizeOfBoard : the size of the board
 * @return FALSE in case the malloc can't allocate memory for the board, TRUE otherwise
 */
int buildGameBoard(const int sizeOfBoard);

/**
 * this function free the memory allocated for the game board.
 * @param sizeOfBoard : the size of the board
 */
void freeGameBoard(const int sizeOfBoard);

/**
 * this function receives a char and returns if its a small letter or not
 * @param ch : the char we want to check
 * @return TRUE if the char is a small english letter. otherwise FALSE.
 */
int isLetter(char ch);

/**
 * this function adds a sunk ship to the counter to know how many ships are left in the game.
 * it checks if all the ship where sunk and if the answer is positive than it finishes the game
 */
void addSunkShip(void);

/**
 * this function gets the move from the user and checks its validation.
 * @param row : the pointer for the row var that will set in the input value
 * @param column : the pointer for the col var that will set in the input value
 * @param sizeOfBoard : the size of the game board.
 * @return FALSE in case the input is not valid, TRUE otherwise
 */
int getMove(int *row, int *column, const int sizeOfBoard);

/**
 * this function checks if the ship that just got hit sunk also. we get its coordinates.
 * @param row : the index of the row
 * @param col : the index of the col
 * @return TRUE if the ship is sunk, FALSE otherwise
 */
int isSunk(const int row, const int col);

/**
 *this function places the move that the user inserted. it prints to the screen the matched
 * massage according to the move that was made (already made, miss, hit, hit and sunk)
 * @param row : the index of the row for the move
 * @param column : the index of the column for the move
 */
void placeMove(const int row, const int column);

/**
 * this function prints the game board.
 * @param sizeOfBoard : the size of the game board
 */
void printBoard(const int sizeOfBoard);

/**
 * this function activates a single round in the game.
 * @param sizeOfBoard : the size of the game board
 */
void playSingleRound(const int sizeOfBoard);

/**
 * @brief this function terminates the game. prints game over and the final board.
 * @note here we use the free function for the allocation of the game board
 * @param sizeOfBoard
 */
void endGame(const int sizeOfBoard);

/**
 * this function gets the size of the board from the user
 * @param sizeOfBoard : the pointer for the size of the board. here we set the size
 * @return TRUE if the size is valid and FALSE otherwise
 */
int getSizeOfBoard(int *sizeOfBoard);

/**
 * this function runs the rounds of the game in a loop until the game is over
 * @param sizeOfBoard : the size of the board
 */
void playGame(const int sizeOfBoard);

/**
 * the main function that runs the game.
 * @return 0 for a standard exit from the program, 1 for an exit because of an error in the program
 */
int main();
