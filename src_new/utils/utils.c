#include <include.h>

void unused(void* obj) {
    void* other = obj;
    obj = other;
}