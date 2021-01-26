#include <include.h>

bool isLobby() {
    return !access(file_lobby, F_OK);
}

Player joinLobby() {
    char* message = tlkRecv(file_lobby);
    if (*message == 'b') return WHITE;
    if (*message == 'w') return BLACK;
    else
        fprintf(stderr, 
            "Host returned bad value when "
            "trying to connect to .lobby "
            "via joinLobby() function.\n"
        );
    return NONE;
}

static int waitForPlayer(void* arg) {
    unused(arg);
    if (tlkSendAsync(file_lobby, "%c", player) > 0) {
        UIStackVisibleName(ui_stack, scene_game);
        return false;
    }
    return true;
}

void hostLobby() {
    UIStackVisibleName(ui_stack, scene_lobby);
    g_timeout_add(250, waitForPlayer, NULL);
    createGame();
}

void createLobby() {
    UI box = UICreateVBox(true);
    UI label = UICreateLabel(txt_lobbyWait);
    UIAppend(box, label);
    UISetID(box, "jumbo");
    UIStackAdd(ui_stack, box, scene_lobby);
}