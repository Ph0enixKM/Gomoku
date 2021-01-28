#include <include.h>

static bool playerCheck(Player color) {
    // Horizontal check
    for (int y = 0; y < size; y++) {
        int count = 0;
        for (int x = 0; x < size; x++)
            if (fields[y * size + x] == color) {
                if (count < winReq)
                    trace[count] = (Pos) {
                        .x = x,
                        .y = y
                    };
                count++;
            }
            else {
                if (count == winReq)
                    return true;
                count = 0;
            }
    }
    // Vertical check
    for (int x = 0; x < size; x++) {
        int count = 0;
        for (int y = 0; y < size; y++)
            if (fields[y * size + x] == color) {
                if (count < winReq)
                    trace[count] = (Pos) {
                        .x = x,
                        .y = y
                    };
                count++;
            }
            else {
                if (count == winReq)
                    return true;
                count = 0;
            }
    }
    // 135 degree diagonal check
    for (int o = -size; o < size; o++) {
        int count = 0;
        for (int x = 0; x < size; x++) {
            int y = o + x;
            if (y > 0 && fields[y * size + x] == color) {
                if (count < winReq)
                    trace[count] = (Pos) {
                        .x = x,
                        .y = y
                    };
                count++;
            }
            else  {
                if (count == winReq)
                    return true;
                count = 0;
            }
        }
    }
    // 45 degree diagonal check
    for (int o = 2 * size; o >= 0; o--) {
        int count = 0;
        for (int y = 0; y < 15; y++) {
            int x = o - y;
            if (x < size && fields[y * size + x] == color) {
                if (count < winReq)
                    trace[count] = (Pos) {
                        .x = x,
                        .y = y
                    };
                count++;
            }
            else {
                if (count == winReq)
                    return true;
                count = 0;
            }
        }
    }
    nullize(trace);
    return false;
}

void gameCheck() {
    bool fullBoard = true;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (fields[y * size + x] == 0) {
                fullBoard = false;
                break;
            }
        }
    }
    char* file = (player == BLACK) 
        ? file_blackDump 
        : file_whiteDump;
    if (fullBoard) {
        UISetLabelText(ui_status, txt_endFull);
        tlkSend(file, "full");
        gameOver('f');
    }
    if (playerCheck(BLACK)) {
        UISetLabelText(ui_status, (player == BLACK ? txt_endWin : txt_endLoose));
        tlkSend(file, "black");
        gameOver('b');
    }
    if (playerCheck(WHITE)) {
        UISetLabelText(ui_status, (player == WHITE ? txt_endWin : txt_endLoose));
        tlkSend(file, "white");
        gameOver('w');
    }
}