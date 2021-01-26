#ifndef GOMOKU_TALK
#define GOMOKU_TALK

void tlkSetBuffer(int size);
int tlkSend(const char* filename, const char* format, ...);
int tlkSendAsync(const char* filename, const char* format, ...);
char* tlkRecv(const char* filename);
char* tlkRecvAsync(const char* filename);
void tlkWrite(const char* filename, const char* format, ...);
char* tlkRead(const char* filename);

#endif