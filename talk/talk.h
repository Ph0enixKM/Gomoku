#ifndef GOMOKU_TALK
#define GOMOKU_TALK

typedef enum {
    TLK_READ,
    TLK_WRITE
} TlkMode;

typedef struct {
    TlkMode mode;
    int buffer;
    bool open;
    int fd;
} TlkPipe;

TlkPipe tlkPipeCreate(const char* filename, int buffer, TlkMode mode);
int tlkPipeSend(TlkPipe* this, const char* format, ...);
char* tlkPipeRecv(TlkPipe* this);
void tlkPipeRemove(TlkPipe* this);

void tlkSetBuffer(int size);
int tlkSend(const char* filename, const char* format, ...);
int tlkSendAsync(const char* filename, const char* format, ...);
char* tlkRecv(const char* filename);
char* tlkRecvAsync(const char* filename);
void tlkWrite(const char* filename, const char* format, ...);
char* tlkRead(const char* filename);

#endif