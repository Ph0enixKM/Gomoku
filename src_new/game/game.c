#include <include.h>

static GdkPixbuf* resize(GdkPixbuf* data, int width, int height) {
    return gdk_pixbuf_scale_simple(data, width, height, GDK_INTERP_BILINEAR);
}

static void turnPawn(UI this, int* pos) {
    int place = pos[1] * size + pos[0];
    if (!fields[place] && turn) {
        char text[8] = "";
        UI field = btns[place];
        UI img = UILoadImage( (player == 'w')
            ? resize(img_whitePawn, 30, 30)
            : resize(img_blackPawn, 30, 30)
        );
        unused(this);
        gtk_button_set_image(GTK_BUTTON(field), img);
        sprintf(text, "%d %d", pos[0], pos[1]);
        fields[place] = player;
        // state = tlkSend(chat, text);
        // turnWait();
    }
}

void createGame() {
    UI color = UILoadImage(img_blackPawn);
    UI header = UICreateHBox(true);
    UI vbox = UICreateVBox(false);
    UI grid = UICreateGrid(true);
    ui_status = UICreateLabel(txt_statusMove);
    UISetID(header, "header");
    turn = true;
    if (player == WHITE) {
        color = UILoadImage(img_whitePawn);
        UISetLabelText(ui_status, txt_statusWait);
        turn = false;
    }
    UIAppend(header, color);
    UIAppend(header, ui_status);
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            UI field = UICreateButton("");
            int* pos = malloc(2 * sizeof(int));
            UIEvent(field, "clicked", turnPawn, pos);
            UIAttach(grid, field, x, y, 1, 1);
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
    UIAppend(vbox, grid);
    UIStackAdd(ui_stack, vbox, scene_game);
}