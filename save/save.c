#include <include.h>

void saveGame(void) {
    UI dialog = gtk_file_chooser_dialog_new(
        "Save File", GTK_WINDOW(ui_window), GTK_FILE_CHOOSER_ACTION_SAVE,
        "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
    int res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char* filename = gtk_file_chooser_get_filename(
            GTK_FILE_CHOOSER(dialog)
        );
        tlkWrite(filename, "%c:%s", player, fields);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void loadGame(void) {
    UI dialog = gtk_file_chooser_dialog_new(
        "Save File", GTK_WINDOW(ui_window), GTK_FILE_CHOOSER_ACTION_OPEN,
        "Cancel", GTK_RESPONSE_CANCEL, "Load", GTK_RESPONSE_ACCEPT, NULL);
    int res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char* filename = gtk_file_chooser_get_filename(
            GTK_FILE_CHOOSER(dialog)
        );
        char* text = tlkRead(filename);
        char symbol = 0;
        int count = sscanf(text, "%c:%s", &symbol, (char*)fields);
        player = symbol;
        if (count != 2)
            UIError("The game save could not be loaded");
        else
            hostLobby(true);
        g_free(filename);
        free(text);
    }
    gtk_widget_destroy(dialog);
}