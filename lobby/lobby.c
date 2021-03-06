#include <include.h>

static bool load = false;

bool isLobby() {
    return !access(file_lobby, F_OK);
}

Player joinLobby() {
    char* message = tlkRecv(file_lobby);
    connected = true;
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
        if (load) {
            char* file = getGameDumpFile();
            tlkSend(file, "load:%s", fields);
            load = false;
        }
        connected = true;
        return false;
    }
    return true;
}

void hostLobby(bool loadFile) {
    if (loadFile) load = true;
    UIStackVisibleName(ui_stack, scene_lobby);
    g_timeout_add(250, waitForPlayer, NULL);
    createGame(load);
    host = true;
}

void createLobby() {
    UI box = UICreateVBox(true);
    UI label = UICreateLabel(txt_lobbyWait);
    UIAppend(box, label);
    UISetID(box, "jumbo");
    UIStackAdd(ui_stack, box, scene_lobby);
}