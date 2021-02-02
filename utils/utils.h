#ifndef GOMOKU_UTILS
#define GOMOKU_UTILS

//! Resize any PixBuf (Image)
GdkPixbuf* resize(GdkPixbuf* data, int width, int height);

//! Use this function if you want to
//! supress "unused variable" warning
void unused(void* obj);

//! Fill an array of positions with nulls
void nullize(Pos* arr);

//! Check whether array 
//! of positions is nullized
bool isNullized(Pos* arr);

//! Sets all the values to zero
//! The reason is that it's hard
//! to save file with null chars
void emptyFields(char* fields);

//! Get correct communication file
char* getGameDumpFile(void);

#endif