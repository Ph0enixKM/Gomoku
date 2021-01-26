#include <include.h>

int main(int argc, char* argv[]) {
    initGlobal();
    gtk_init(&argc, &argv);
    UILoadCSS("assets/style.css");
    ui_stack = UICreateStack();
    // Create window
    ui_window = UICreateWindow("Gomoku", (WindowConfig) {
        .width = 600,
        .height = 700,
        .center = true,
        .resizable = true,
        .border = 0,
        .exit = true
    });
    UIAppend(ui_window, ui_stack);
    // Create all the required scenes
    createLobby();
    createMenu();
    createEnd();
    // Join to a lobby (if exists)
    if (isLobby()) {
        player = joinLobby();
        createGame();
        UIStackVisibleName(ui_stack, scene_game);
        remove(file_lobby);
    }
    // Enter menu otherwise
    else {
        UIStackVisibleName(ui_stack, scene_menu);
    }
    gtk_main();
    deleteGlobal();
}