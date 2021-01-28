#include <include.h>

static UI menu_stack = NULL;

static void menuPawn(UI this, char* data) {
    player = (*data == 'b') ? BLACK : WHITE;
    unused(this);
    hostLobby();
}

static void joinGame() {
    player = joinLobby();
    createGame();
    UIStackVisibleName(ui_stack, scene_game);
    remove(file_lobby);
}

static int seekLobby(void* this) {
    unused(this);
    if (isLobby()) {
        UIStackVisibleName(menu_stack, "join");
    }
    else {
        UIStackVisibleName(menu_stack, "host");
    }
    if (connected) return false;
    return true;
}

void createMenu(void) {
    UI logo = UILoadImage(img_logo);
    UI hbox = UICreateHBox(true);
    menu_stack = UICreateStack();
    UI vbox = UICreateVBox(true);
    UIStackAdd(ui_stack, vbox, scene_menu);
    // Create a Join
    UI join = UICreateButton("Join Game");
    UIAddClass(join, "btn-img");
    UISetID(join, "join");
    UIEvent(join, "clicked", joinGame, NULL);
    g_timeout_add(250, seekLobby, NULL);
    // Add to a stack
    UIStackAdd(menu_stack, hbox, "host");
    UIStackAdd(menu_stack, join, "join");
    UIStackVisibleName(menu_stack, "host");
    // Create a menu
    UISetID(vbox, "menu");
    UIAppend(vbox, logo);
    UIAppend(vbox, menu_stack);
    // Black pawn
    UI black = UICreateButton("");
    UI blackImage = UILoadImage(img_blackPawn);
    gtk_button_set_image(GTK_BUTTON(black), blackImage);
    UIAddClass(black, "btn-img");
    UIAddClass(black, "menu-pawn");
    // Create a white pawn
    UI white = UICreateButton("");
    UI whiteImage = UILoadImage(img_whitePawn);
    gtk_button_set_image(GTK_BUTTON(white), whiteImage);
    UIAddClass(white, "btn-img");
    UIAddClass(white, "menu-pawn");
    // Append all the base elements
    UIAppend(hbox, black);
    UIAppend(hbox, white);
    UIEvent(black, "clicked", menuPawn, "b");
    UIEvent(white, "clicked", menuPawn, "w");
}