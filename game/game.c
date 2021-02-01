#include <include.h>

static void updateButtons() {
    for (int i = 0; i < size * size; i++) {
        if (fields[i] != NONE) {
            UI btn = btns[i];
            UI img = UILoadImage((fields[i] == (char)BLACK)
                ? resize(img_blackPawn, 30, 30)
                : resize(img_whitePawn, 30, 30)
            );
            gtk_button_set_image(GTK_BUTTON(btn), img);
            UIAddClass(btn, "occupied");
        }
    }
}

static void turnMove() {
    turn = true;
    UISetLabelText(ui_status, txt_statusMove);
    UIRemoveClass(ui_grid, "wait");
    gameCheck();
}

static void turnWait() {
    turn = false;
    UISetLabelText(ui_status, txt_statusWait);
    UIAddClass(ui_grid, "wait");
}

static void turnPawn(UI this, int* pos) {
    int place = pos[1] * size + pos[0];
    if (fields[place] == NONE && turn) {
        UI btn = btns[place];
        UI img = UILoadImage((player == WHITE)
            ? resize(img_whitePawn, 30, 30)
            : resize(img_blackPawn, 30, 30)
        );
        unused(this);
        fields[place] = player;
        gtk_button_set_image(GTK_BUTTON(btn), img);
        UIAddClass(btn, "occupied");
        char* file = getGameDumpFile();
        tlkSetBuffer(gameBuffer);
        tlkSend(file, "%d %d", pos[0], pos[1]);
        turnWait();
    }
}

static bool turnEnd(char* msg) {
    switch (msg[0]) {
        // Full board
        case 'f':
            gameCheck();
            connected = false;
            return true;
        break;
        // Black wins
        case 'b':
            gameCheck();
            connected = false;
            return true;
        break;
        // White wins
        case 'w':
            gameCheck();
            connected = false;
            return true;
        break;
        // Disconnected
        case 'd':
            turnWait();
            UISetLabelText(ui_status, txt_endLeft);
            connected = false;
            return true;
        break;
        // Load game
        case 'l':
            sscanf(msg, "load:%s", fields);
            updateButtons();
            return false;
        break;
    }
    return false;
}

static int turnWaitLoop(void* arg) {
    unused(arg);
    char* text = (player == WHITE) 
        ? tlkPipeRecv(&blackDump) 
        : tlkPipeRecv(&whiteDump);
    if (text != NULL) {
        if (turnEnd(text)) return false;
        if (text[0] != '\0' && text[0] <= '9' && !turn) {
            int x, y;
            sscanf(text, "%d %d", &x, &y);
            int place = y * size + x;
            UI btn = btns[place];
            fields[place] = (player == BLACK ? 'w' : 'b');
            UI img = UILoadImage((player == BLACK)
                ? resize(img_whitePawn, 30, 30)
                : resize(img_blackPawn, 30, 30)
            );
            gtk_button_set_image(GTK_BUTTON(btn), img);
            UIAddClass(btn, "occupied");
            turnMove();
        }
    }
    return true;
}

void gameOver(char symbol) {
    UIAddClass(ui_grid, "wait");
    turn = false;
    if (!isNullized(trace)) {
        for (int i = 0; i < winReq; i++) {
            int place = trace[i].y * size + trace[i].x;
            UI field = btns[place];
            UIAddClass(field, "trace");
            if (player == (unsigned)symbol)
                UIAddClass(field, "win");
        }
    }
    gtk_widget_set_sensitive (ui_save, false);
}

static void eventExit() {
    for (int i = 0; i < size * size; i++)
        fields[i] = '0';
    gtk_widget_destroy(ui_grid);
    gtk_widget_destroy(ui_status);
    gtk_widget_destroy(ui_save);
    UI stack_child = gtk_stack_get_child_by_name(GTK_STACK(ui_stack), scene_game);
    gtk_widget_destroy(stack_child);
    if (connected) {
        char* file = getGameDumpFile();
        tlkSetBuffer(gameBuffer);
        tlkSend(file, "disconnected");
    }
    turn = false;
    connected = false;
    host = false;
    remove(file_whiteDump);
    remove(file_blackDump);
    UIStackVisibleName(ui_stack, scene_menu);
    seekLobbyWorker();
}

void createGame(bool load) {
    UI color = UILoadImage(img_blackPawn);
    UI header = UICreateGrid(true);
    UI vbox = UICreateVBox(false);
    ui_grid = UICreateGrid(true);
    ui_status = UICreateLabel("");
    UISetID(header, "header");
    if (player == WHITE) {
        color = UILoadImage(img_whitePawn);
    }
    UI exit = UICreateButton("");
    gtk_button_set_image(GTK_BUTTON(exit), UILoadImage(resize(img_exit, 40, 40)));
    gtk_widget_set_tooltip_text(exit, "Exit to menu");
    UIAddClass(exit, "btn-img");
    UIEvent(exit, "clicked", eventExit, NULL);

    ui_save = UICreateButton("");
    gtk_widget_set_tooltip_text(ui_save, "Save");
    gtk_button_set_image(GTK_BUTTON(ui_save), UILoadImage(resize(img_save, 30, 30)));
    UIAddClass(ui_save, "btn-img");
    UIEvent(ui_save, "clicked", saveGame, NULL);

    UIAttach(header, exit, 0, 0, 1, 1);
    UIAttach(header, ui_save, 0, 1, 1, 1);
    UIAttach(header, color, 1, 0, 2, 2);
    UIAttach(header, ui_status, 3, 0, 3, 2);
    gtk_widget_set_size_request(ui_status, 150, 50);
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            UI field = UICreateButton("");
            int* pos = malloc(2 * sizeof(int));
            UIEvent(field, "clicked", turnPawn, pos);
            UIAttach(ui_grid, field, x, y, 1, 1);
            gtk_widget_set_size_request(field, 40, 40);
            UIAddClass(field, ((x + y) % 2)
                ? "black-field"
                : "white-field"
            );
            btns[y * size + x] = field;
            pos[0] = x;
            pos[1] = y;
        }
    }
    UIAppend(vbox, header);
    UIAppend(vbox, ui_grid);
    UIStackAdd(ui_stack, vbox, scene_game);
    if (player == BLACK) {
        whiteDump = tlkPipeCreate(
            file_whiteDump, 
            gameBuffer, 
            TLK_READ
        );
        turnMove();
    }
    else {
        blackDump = tlkPipeCreate(
            file_blackDump, 
            gameBuffer, 
            TLK_READ
        );
        turnWait();
    }
    if (load) updateButtons();
    g_timeout_add(16, turnWaitLoop, NULL);
}
