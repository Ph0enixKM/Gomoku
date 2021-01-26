#include <include.h>

#ifndef GOMOKU_INCLUDE
#define GOMOKU_INCLUDE

// Elements
UI ui_window = NULL;
UI ui_stack = NULL;
UI ui_status = NULL;
UI ui_verdict = NULL;

// Data
Player player = NONE;
bool turn = false;
int size = 15;
int winReq = 5;
char* verdict = NULL;
int* fields = NULL;
UI* btns = NULL;

// Files
const char* file_lobby = ".lobby";
const char* file_chat = ".chat";

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

// Scenes
const char* scene_menu = "menu";
const char* scene_game = "game";
const char* scene_lobby = "lobby";
const char* scene_end = "end";

void initGlobal(void) {
    verdict = txt_endLeft;
    fields = calloc(size * size, sizeof(int));
    btns = calloc(size * size, sizeof(UI));
    // Load images
    img_logo = UILoadImageData("assets/logo.png");
    img_whitePawn = UILoadImageData("assets/white-pawn.png");
    img_blackPawn = UILoadImageData("assets/black-pawn.png");
}

void deleteGlobal(void) {
    free(fields);
    free(btns);
}

#endif