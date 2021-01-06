#include <stdio.h>
#include <gtkui.h>
#include "talk.h"
#include <pthread.h>

#define N 15

UI window;
UI stack;
const char* lobby = ".lobby";
const char* chat = ".chat";
char player = ' ';
bool turn = false;
int fields[N*N] = {};
UI btns[N*N] = {};
UI status;
const char* statusWait = "Wait for your turn...";
const char* statusMove = "Your turn!";

struct Pos {
    int x;
    int y;
};

struct Images {
    GdkPixbuf* logo;
    GdkPixbuf* whitePawn;
    GdkPixbuf* blackPawn;
} images;

struct Scenes {
  const char* menu;
  const char* game;
  const char* wait;
} scenes = {
    .menu = "menu",
    .game = "game",
    .wait = "wait"
};

void loadImages(void) {
    images.logo = UILoadImageData("public/logo.png");
    images.whitePawn = UILoadImageData("public/white-pawn.png");
    images.blackPawn = UILoadImageData("public/black-pawn.png");
}

void unused(void* obj) {
    void* other = obj;
    obj = other;
}

void updateWindow() {
    while(gtk_events_pending()) gtk_main_iteration();
    for (int i = 0; i < 24; i++) gtk_main_iteration();
}

void turnMove() {
    gtk_label_set_text(GTK_LABEL(status), statusMove);
    turn = true;
    updateWindow();
}

void turnWait(void) {
    turn = false;
    gtk_label_set_text(GTK_LABEL(status), statusWait);
    updateWindow();
    int x, y;
    char* msg = Talk.recv(chat);
    sscanf(msg, "%d %d", &x, &y);
    UI field = btns[y*N+x];
    UISetID(field, (player == 'b' ? "white-pawn" : "black-pawn"));
    turnMove();
}

void turnPawn(UI this, int* pos) {
    if (turn) {
        unused(this);
        char text[8] = "";
        UI field = btns[pos[1]*N+pos[0]];
        UISetID(field, (player == 'w' ? "white-pawn" : "black-pawn"));
        sprintf(text, "%d %d", pos[0], pos[1]);
        updateWindow();
        Talk.send(chat, text);
        turnWait();
    }
}

void createGame() {
    UI vbox = UICreateVBox();
    UI header = UICreateHBox();
    gtk_box_set_homogeneous(GTK_BOX(header), true);
    UISetID(header, "header");
    status = UICreateLabel(statusWait);
    UI color;
    if (player == 'b')
        color = UILoadImage(images.blackPawn);
    else
        color = UILoadImage(images.whitePawn);
    UIAppend(header, color);
    UIAppend(header, status);
    UI grid = UICreateGrid(true);
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            UI field = UICreateButton("");
            UIAddClass(field, ((x+y) % 2) ? "black-field" : "white-field");
            btns[y*N+x] = field;
            UIAttach(grid, field, x, y, 1, 1);
            int* pos = malloc(2*sizeof(int));
            pos[0] = x;
            pos[1] = y;
            UIEvent(field, "clicked", turnPawn, pos);
        }
    }
    UIAppend(vbox, header);
    UIAppend(vbox, grid);
    UIStackAdd(stack, vbox, "game");

    if (player == 'b') {
        turnMove();
    }
}

void* createLobbyWait(void* arg) {
    unused(arg);
    Talk.send(lobby, (const char*)arg);
    printf("CREATED\n");
    return NULL;
}

void createLobbyEvent(UI this, const char* color) {
    pthread_t id;
    unused(this);
    UIStackVisibleName(stack, scenes.wait);
    updateWindow();
    player = *color;
    createGame();
    pthread_create(&id, NULL, createLobbyWait, (void*)color);
    pthread_join(id, NULL);
    UIStackVisibleName(stack, scenes.game);
}

void createWait(void) {
    UI cont = UICreateLabel("Waiting for other player...");
    UISetID(cont, "wait");
    UIStackAdd(stack, cont, "wait");
}

void createMenu(void) {
    UI logo = UILoadImage(images.logo);
    UI grid = UICreateGrid(true);
    UI vbox = UICreateVBox();
    UISetID(vbox, "menu");
    UIStackAdd(stack, vbox, "menu");
    gtk_box_set_homogeneous(GTK_BOX(vbox), true);
    UIAppend(vbox, logo);
    UIAppend(vbox, grid);
    // Black pawn
    UI black = UICreateButton("");
    UI blackPawn = UILoadImage(images.blackPawn);
    gtk_button_set_image(GTK_BUTTON(black), blackPawn);
    UIAddClass(black, "btn-img");
    UIAddClass(black, "hover");
    UIEvent(black, "clicked", createLobbyEvent, "b");
    UIAttach(grid, black, 0, 0, 1, 1);
    // Space between pawns
    UI spacing = UICreateVBox();
    UIAttach(grid, spacing, 1, 0, 1, 1);
    // White pawn
    UI white = UICreateButton("");
    UI whitePawn = UILoadImage(images.whitePawn);
    gtk_button_set_image(GTK_BUTTON(white), whitePawn);
    UIAddClass(white, "btn-img");
    UIAddClass(white, "hover");
    UIEvent(white, "clicked", createLobbyEvent, "w");
    UIAttach(grid, white, 2, 0, 1, 1);
}

void* pturnWait(void* arg) {
    unused(arg);
    turnWait();
    return NULL;
}

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    window = UICreateWindow("Gomoku", (WindowConfig) {
        .width = 600,
        .height = 600,
        .center = true,
        .resizable = true,
        .border = 0,
        .exit = true
    });
    loadImages();
    UILoadCSS("public/style.css");
    stack = UICreateStack();
    createWait();

    // If lobby exists
    if (!access(lobby, F_OK)) {
        player = *Talk.recv(lobby);
        player = (player == 'b' ? 'w' : 'b');
        createGame();
        remove(lobby);
        UIStackVisibleName(stack, scenes.game);
        pthread_t id;
        pthread_create(&id, NULL, pturnWait, NULL);
    }
    else {
        createMenu();
        UIStackVisibleName(stack, scenes.menu);
    }

    UIAppend(window, stack);
    gtk_main();

    
}