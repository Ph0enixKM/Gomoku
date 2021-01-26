#include <include.h>

static GdkPixbuf* resize(GdkPixbuf* data, int width, int height) {
    return gdk_pixbuf_scale_simple(data, width, height, GDK_INTERP_BILINEAR);
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
    if (!fields[place] && turn) {
        UI field = btns[place];
        UI img = UILoadImage((player == WHITE)
            ? resize(img_whitePawn, 30, 30)
            : resize(img_blackPawn, 30, 30)
        );
        unused(this);
        fields[place] = player;
        gtk_button_set_image(GTK_BUTTON(field), img);
        UIAddClass(field, "occupied");
        char* file = (player == BLACK) 
            ? file_blackDump 
            : file_whiteDump;
        tlkSetBuffer(gameBuffer);
        tlkSend(file, "%d %d", pos[0], pos[1]);
        turnWait();
    }
}

static bool turnEnd(char* msg) {
    if (msg[0] == 'f') {
        gameCheck();
        return true;
    }
    if (msg[0] == 'b') {
        gameCheck();
        return true;
    }
    if (msg[0] == 'w') {
        gameCheck();
        return true;
    }
    return false;
}

static int turnWaitLoop(void* arg) {
    if (!turn) {
        unused(arg);
        char* text = (player == WHITE) 
            ? tlkPipeRecv(&blackDump) 
            : tlkPipeRecv(&whiteDump);
        if (text != NULL) {
                if (turnEnd(text)) return false;
                int x, y;
                sscanf(text, "%d %d", &x, &y);
                int place = y * size + x;
                UI field = btns[place];
                fields[place] = (player == BLACK ? 'w' : 'b');
                UI img = UILoadImage((player == BLACK)
                    ? resize(img_whitePawn, 30, 30)
                    : resize(img_blackPawn, 30, 30)
                );
                gtk_button_set_image(GTK_BUTTON(field), img);
                UIAddClass(field, "occupied");
                turnMove();
        }
    }
    return true;
}

void gameOver() {
    UIAddClass(ui_grid, "wait");
    turn = false;
    if (!isNullized(trace)) {
        for (int i = 0; i < winReq; i++) {
            int place = trace[i].y * size + trace[i].x;
            UI field = btns[place];
            UIAddClass(field, "trace");
        }
    }
}

void createGame() {
    UI color = UILoadImage(img_blackPawn);
    UI header = UICreateHBox(true);
    UI vbox = UICreateVBox(false);
    ui_grid = UICreateGrid(true);
    ui_status = UICreateLabel("");
    UISetID(header, "header");
    if (player == WHITE) {
        color = UILoadImage(img_whitePawn);
    }
    UIAppend(header, color);
    UIAppend(header, ui_status);
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
    g_timeout_add(1, turnWaitLoop, NULL);
}