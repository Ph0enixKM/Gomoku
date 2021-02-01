#include <include.h>

GdkPixbuf* resize(GdkPixbuf* data, int width, int height) {
    return gdk_pixbuf_scale_simple(data, width, height, GDK_INTERP_BILINEAR);
}

void unused(void* obj) {
    void* other = obj;
    obj = other;
}

void nullize(Pos* arr) {
    arr[0] = (Pos) {
        .x = -1,
        .y = -1
    };
}

bool isNullized(Pos* arr) {
    if (arr[0].x + arr[0].y == -2)
        return true;
    return false;
}

void emptyFields(char* fields) {
    for (int i = 0; i < size * size; i++)
        fields[i] = '0';
}

char* getGameDumpFile(void) {
    if (player == BLACK)
        return file_blackDump;
    return file_whiteDump;
}