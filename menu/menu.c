#include <include.h>

static UI menu_stack = NULL;
static UI host_stack = NULL;

static void menuPawn(UI this, char* data) {
    player = (*data == 'b') ? BLACK : WHITE;
    unused(this);
    hostLobby(false);
}

static void joinGame(void) {
    player = joinLobby();
    createGame(false);
    UIStackVisibleName(ui_stack, scene_game);
    remove(file_lobby);
}

static int seekLobby(void* this) {
    unused(this);
    if (isLobby())
        UIStackVisibleName(menu_stack, "join");
    else
        UIStackVisibleName(menu_stack, "host");
    if (connected) return false;
    return true;
}

static void changeHostMenu(void* this, char* name) {
    unused(this);
    UIStackVisibleName(host_stack, name);
}

void seekLobbyWorker(void) {
    g_timeout_add(250, seekLobby, NULL);
}

static void createHostMenu() {
    /////
    // Main
    ////

    // Menu of host stack
    UI main = UICreateGrid(true);
    UIStackAdd(host_stack, main, "main");
    // New game button
    UI main_newGame = UICreateButton("");
    gtk_button_set_image(GTK_BUTTON(main_newGame), 
        UILoadImage(resize(img_newGame, 100, 100))
    );
    gtk_widget_set_tooltip_text(main_newGame, "Host a new game");
    UIAddClass(main_newGame, "btn-img");
    UIAddClass(main_newGame, "menu-item");
    // Load game button
    UI main_loadGame = UICreateButton("");
    gtk_button_set_image(GTK_BUTTON(main_loadGame), 
        UILoadImage(resize(img_load, 100, 100))
    );
    gtk_widget_set_tooltip_text(main_loadGame, "Host a saved game");
    UIAddClass(main_loadGame, "btn-img");
    UIAddClass(main_loadGame, "menu-item");
    // Attach buttons
    UIAttach(main, main_newGame, 0, 1, 1, 1);
    UIAttach(main, main_loadGame, 2, 1, 1, 1);
    UIEvent(main_newGame, "clicked", changeHostMenu, "new");
    UIEvent(main_loadGame, "clicked", loadGame, NULL);

    /////
    // New Game
    ////

    // New Game host menu
    UI newGame = UICreateGrid(true);
    UIStackAdd(host_stack, newGame, "new");
    // Exit button
    UI newGame_exit = UICreateButton("");
    UIAddClass(newGame_exit, "btn-img");
    gtk_button_set_image(GTK_BUTTON(newGame_exit), 
        UILoadImage(resize(img_exit, 100, 100))
    );
    // Create a Black pawn
    UI black = UICreateButton("");
    UI blackImage = UILoadImage(img_blackPawn);
    gtk_button_set_image(GTK_BUTTON(black), blackImage);
    gtk_widget_set_tooltip_text(black, "Host game with a black pawn");
    UIAddClass(black, "btn-img");
    UIAddClass(black, "menu-item");
    // Create a white pawn
    UI white = UICreateButton("");
    UI whiteImage = UILoadImage(img_whitePawn);
    gtk_button_set_image(GTK_BUTTON(white), whiteImage);
    gtk_widget_set_tooltip_text(white, "Host game with a white pawn");
    UIAddClass(white, "btn-img");
    UIAddClass(white, "menu-item");
    // Attach to a host new game menu
    UIAttach(newGame, UICreateLabel("Host game"), 0, 0, 3, 1);
    UIAttach(newGame, black, 0, 1, 1, 1);
    UIAttach(newGame, white, 2, 1, 1, 1);
    UIAttach(newGame, newGame_exit, 0, 2, 3, 1);
    UIEvent(black, "clicked", menuPawn, "b");
    UIEvent(white, "clicked", menuPawn, "w");
    UIEvent(newGame_exit, "clicked", changeHostMenu, "main");
    
    // Show the host stack
    UIStackVisibleName(host_stack, "main");
}

void createMenu(void) {
    UI logo = UILoadImage(img_logo);
    host_stack = UICreateStack();
    menu_stack = UICreateStack();
    UI vbox = UICreateVBox(true);
    UIStackAdd(ui_stack, vbox, scene_menu);
    // Create a Join
    UI join = UICreateButton("Join Game");
    UIAddClass(join, "btn-img");
    UISetID(join, "join");
    UIEvent(join, "clicked", joinGame, NULL);
    // Add to a stack
    UIStackAdd(menu_stack, host_stack, "host");
    UIStackAdd(menu_stack, join, "join");
    UIStackVisibleName(menu_stack, "host");
    seekLobbyWorker();
    // Create a menu
    UISetID(vbox, "menu");
    UIAppend(vbox, logo);
    UIAppend(vbox, menu_stack);
    createHostMenu();
}