#include <include.h>

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
