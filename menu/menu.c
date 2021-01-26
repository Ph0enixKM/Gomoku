#include <include.h>

static void menuPawn(UI this, char* data) {
    player = (*data == 'b') ? BLACK : WHITE;
    unused(this);
    hostLobby();
}

void createMenu(void) {
    UI logo = UILoadImage(img_logo);
    UI hbox = UICreateHBox(true);
    UI vbox = UICreateVBox(true);
    UIStackAdd(ui_stack, vbox, scene_menu);
    UISetID(vbox, "menu");
    UIAppend(vbox, logo);
    UIAppend(vbox, hbox);
    // Black pawn
    UI black = UICreateButton("");
    UI blackImage = UILoadImage(img_blackPawn);
    gtk_button_set_image(GTK_BUTTON(black), blackImage);
    UIAddClass(black, "btn-img");
    // Create a space
    UI space = UICreateVBox(false);
    // Create a white pawn
    UI white = UICreateButton("");
    UI whiteImage = UILoadImage(img_whitePawn);
    gtk_button_set_image(GTK_BUTTON(white), whiteImage);
    UIAddClass(white, "btn-img");
    // Append all the base elements
    UIAppend(hbox, black);
    UIAppend(hbox, space);
    UIAppend(hbox, white);
    UIEvent(black, "clicked", menuPawn, "b");
    UIEvent(white, "clicked", menuPawn, "w");
}