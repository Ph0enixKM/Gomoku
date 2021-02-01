#include <include.h>

#ifndef GOMOKU_INCLUDE
#define GOMOKU_INCLUDE

// Elements
UI ui_window = NULL;
UI ui_stack = NULL;
UI ui_status = NULL;
UI ui_grid = NULL;
UI ui_save = NULL;

// Data
Player player = NONE;
char* fields = NULL;
bool turn = false;
int size = 15;
int winReq = 5;
Pos* trace = NULL;
UI* btns = NULL;
int gameBuffer = 64;
bool host = false;
bool connected = false;

// Pipes
TlkPipe whiteDump;
TlkPipe blackDump;

// Files
char* file_lobby = ".lobby";
char* file_whiteDump = ".white-dump";
char* file_blackDump = ".black-dump";

// Text messages
char* txt_lobbyWait = "Waiting for player";
char* txt_statusWait = "Wait for your turn...";
char* txt_statusMove = "Your turn!";
char* txt_endLeft = "Opponent left the game";
char* txt_endWin = "You win";
char* txt_endLoose = "You loose";
char* txt_endFull = "Board is full";

// Images
GdkPixbuf* img_logo = NULL;
GdkPixbuf* img_whitePawn = NULL;
GdkPixbuf* img_blackPawn = NULL;
GdkPixbuf* img_save = NULL;
GdkPixbuf* img_load = NULL;
GdkPixbuf* img_exit = NULL;
GdkPixbuf* img_newGame = NULL;

// Scenes
const char* scene_menu = "menu";
const char* scene_game = "game";
const char* scene_lobby = "lobby";
const char* scene_end = "end";

void initGlobal(void) {
    fields = calloc(size * size, sizeof(char));
    btns = calloc(size * size, sizeof(UI));
    trace = calloc(winReq, sizeof(Pos));
    emptyFields(fields);
    gameBuffer = 2 * size * size;
    // Load images
    img_logo = UILoadImageData("assets/logo.png");
    img_whitePawn = UILoadImageData("assets/white-pawn.png");
    img_blackPawn = UILoadImageData("assets/black-pawn.png");
    img_save = UILoadImageData("assets/save.png");
    img_load = UILoadImageData("assets/load.png");
    img_exit = UILoadImageData("assets/exit.png");
    img_newGame = UILoadImageData("assets/newgame.png");
}

void deleteGlobal(void) {
    if (fields != NULL) {
        free(fields);
        free(btns);
        free(trace);
        fields = NULL;
    }
}

#endif