#ifndef GOMOKU_LOBBY
#define GOMOKU_LOBBY

// Player typedef
typedef enum {
    NONE = -1,
    BLACK = 'b',
    WHITE = 'w'
} Player;

// Create a lobby scene
// in a stack switcher
void createLobby();

// Check if lobby 
// already exists
bool isLobby();

// Join existing lobby
Player joinLobby();

// Host a new lobby
void hostLobby();

#endif