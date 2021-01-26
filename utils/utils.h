#ifndef GOMOKU_UTILS
#define GOMOKU_UTILS

// Use this function if you want to
// supress "unused variable" warning
void unused(void* obj);

// Fill an array of positions with nulls
void nullize(Pos* arr);

// Check whether array 
// of positions is nullized
bool isNullized(Pos* arr);

#endif