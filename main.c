#include <include.h>

static void onExit() {
    deleteGlobal();
    if (host)
        remove(file_lobby);
    if (connected) {
        char* file = (player == BLACK) 
            ? file_blackDump 
            : file_whiteDump;
        tlkSetBuffer(gameBuffer);
        tlkSend(file, "disconnected");
    }
    remove(file_whiteDump);
    remove(file_blackDump);
    exit(0);
}

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
        .resizable = false,
        .border = 0,
        .exit = false
    });
    UIAppend(ui_window, ui_stack);
    // Create all the required scenes
    createLobby();
    createMenu();
    // Open menu
    UIStackVisibleName(ui_stack, scene_menu);
    UIEvent(ui_window, "destroy", onExit, NULL);
    gtk_main();
}
