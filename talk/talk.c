#include <include.h>

static int buffer = 1024;

void tlkSetBuffer(int size) {
    buffer = size;
}

int tlkSend(const char* filename, const char* format, ...) {
    if (access(filename, F_OK)) mkfifo(filename, 0666);
    int fd = open(filename, O_WRONLY);
    char* text = calloc(buffer, sizeof(char));
    va_list argptr;
    va_start(argptr, format);
    vsprintf(text, format, argptr);
    va_end(argptr);
    int state = write(fd, text, buffer);
    close(fd);
    free(text);
    return state;
}

int tlkSendAsync(const char* filename, const char* format, ...) {
    if (access(filename, F_OK)) mkfifo(filename, 0666);
    int fd = open(filename, O_WRONLY | O_NONBLOCK);
    char* text = calloc(buffer, sizeof(char));
    va_list argptr;
    va_start(argptr, format);
    vsprintf(text, format, argptr);
    va_end(argptr);
    int state = write(fd, text, buffer);
    close(fd);
    free(text);
    return state;
}

char* tlkRecvAsync(const char* filename) {
    if (access(filename, F_OK)) mkfifo(filename, 0666);
    int fd = open(filename, O_RDONLY | O_NONBLOCK);
    char* text = calloc(buffer, sizeof(char));
    int size = read(fd, text, buffer);
    close(fd);
    if (size < 1) return NULL;
    return text;
}

char* tlkRecv(const char* filename) {
    if (access(filename, F_OK)) mkfifo(filename, 0666);
    int fd = open(filename, O_RDONLY);
    char* text = calloc(buffer, sizeof(char));
    read(fd, text, buffer);
    close(fd);
    return text;
}

void tlkWrite(const char* filename, const char* format, ...) {
    FILE* file = fopen(filename, "w");
    va_list argptr;
    va_start(argptr, format);
    vfprintf(file, format, argptr);
    va_end(argptr);
    fclose(file);
}

char* tlkRead(const char* filename) {
    FILE* file = fopen(filename, "r");
    char* text = calloc(buffer, sizeof(char));
    fread(text, sizeof(char), buffer, file);
    return text;
}

TlkPipe tlkPipeCreate(const char* filename, int buffer, TlkMode mode) {
    int fd = 0;
    if (access(filename, F_OK)) mkfifo(filename, 0666);
    if (mode == TLK_READ)
        fd = open(filename, O_RDONLY | O_NONBLOCK);
    else
        fd = open(filename, O_WRONLY | O_NONBLOCK);
    return (TlkPipe) {
        .mode = mode,
        .buffer = buffer,
        .open = true,
        .fd = fd
    };
}

int tlkPipeSend(TlkPipe* this, const char* format, ...) {
    if (!this->open) return -1;
    char* text = calloc(this->buffer, sizeof(char));
    va_list argptr;
    va_start(argptr, format);
    vsprintf(text, format, argptr);
    va_end(argptr);
    int state = write(this->fd, text, this->buffer);
    free(text);
    return state;
}

char* tlkPipeRecv(TlkPipe* this) {
    if (!this->open) return NULL;
    char* text = calloc(this->buffer, sizeof(char));
    int size = read(this->fd, text, this->buffer);
    if (size < 1) return NULL;
    return text;
}

void tlkPipeRemove(TlkPipe* this) {
    if (this->open) close(this->fd);
}