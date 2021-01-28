#ifndef GOMOKU
#define GOMOKU

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <glib.h>

#include "gtkui/gtkui.h"
#include "lobby/lobby.h"
#include "talk/talk.h"
#include "menu/menu.h"
#include "game/game.h"
#include "utils/utils.h"

// Init function for variables
// using dynamic memory
void initGlobal(void);

// Free all the memory held
// by all global variables
void deleteGlobal(void);

// Elements
extern UI ui_window;
extern UI ui_status;
extern UI ui_stack;
extern UI ui_grid;

// Data
extern int gameBuffer;
extern bool connected;
extern Player player;
extern int* fields;
extern int winReq;
extern Pos* trace;
extern bool turn;
extern int size;
extern UI* btns;
extern bool host;

// Pipes
extern TlkPipe whiteDump;
extern TlkPipe blackDump;

// Files
extern char* file_lobby;
extern char* file_blackDump;
extern char* file_whiteDump;

// Text messages
extern char* txt_lobbyWait;
extern char* txt_statusWait;
extern char* txt_statusMove;
extern char* txt_endLoose;
extern char* txt_endLeft;
extern char* txt_endFull;
extern char* txt_endWin;

// Images
extern GdkPixbuf* img_whitePawn;
extern GdkPixbuf* img_blackPawn;
extern GdkPixbuf* img_logo;

// Scenes
extern const char* scene_lobby;
extern const char* scene_menu;
extern const char* scene_game;
extern const char* scene_end;

#endif
