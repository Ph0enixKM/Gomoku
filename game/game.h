#ifndef GOMOKU_GAME
#define GOMOKU_GAME

typedef struct {
    int x;
    int y;
} Pos;

// Create a game board
// Remember that this function
// Must be invoked after we 
// Know which color is our player
void createGame();

// Check if this is game over
void gameCheck();

// Show game over
void gameOver();

#endif