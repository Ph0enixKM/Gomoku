#include <include.h>

static int buffer = 1024;

void tlkSetBuffer(int size) {
    buffer = size;
}

int tlkSend(const char* filename, const char* format, ...) {
    mkfifo(filename, 0666);
    int fd = open(filename, O_WRONLY);
    char* text = malloc(buffer * sizeof(char));
    va_list argptr;
    va_start(argptr, format);
    vsprintf(text, format, argptr);
    va_end(argptr);
    int state = write(fd, text, buffer);
    if (state < 0) {
        perror(filename);
    }
    close(fd);
    free(text);
    return state;
}

int tlkSendAsync(const char* filename, const char* format, ...) {
    mkfifo(filename, 0666);
    int fd = open(filename, O_WRONLY | O_NONBLOCK);
    char* text = malloc(buffer * sizeof(char));
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
    mkfifo(filename, 0666);
    int fd = open(filename, O_RDONLY | O_NONBLOCK);
    char* text = malloc(buffer * sizeof(char));
    int size = read(fd, text, buffer);
    close(fd);
    if (size < 1) return NULL;
    return text;
}

char* tlkRecv(const char* filename) {
    mkfifo(filename, 0666);
    int fd = open(filename, O_RDONLY);
    char* text = malloc(buffer * sizeof(char));
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
