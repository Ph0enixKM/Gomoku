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



//////////////////////////////////////////
// Pipe IO functions with structure API //
// which are implemented asynchronously //
//////////////////////////////////////////

// Create Pipe and return an object representation
TlkPipe tlkPipeCreate(const char* filename, int buffer, TlkMode mode);

// Asynchronously send textual information to the pipe
int tlkPipeSend(TlkPipe* this, const char* format, ...);

// Asynchronously receive textual 
// information through the pipe
char* tlkPipeRecv(TlkPipe* this);

// Close opened pipe
void tlkPipeRemove(TlkPipe* this);



//////////////////////////////////
// Standalone pipe IO functions //
//////////////////////////////////

// Set buffer size (default is 1024)
void tlkSetBuffer(int size);

// Send textual infromation through pipe synchronously
int tlkSend(const char* filename, const char* format, ...);

// Send textual information through pip asynchronously
int tlkSendAsync(const char* filename, const char* format, ...);

// Receive textual information synchronously
char* tlkRecv(const char* filename);

// Receive textual information asynchronously
char* tlkRecvAsync(const char* filename);



//////////////////////////////////
// Standalone file IO functions //
//////////////////////////////////

// Write textual information to a file
void tlkWrite(const char* filename, const char* format, ...);

// Read textual information from a file
char* tlkRead(const char* filename);

#endif