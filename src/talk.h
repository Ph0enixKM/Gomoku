#ifndef TALK
#define TALK

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

static int buffer = 1024;
static void setBuffer(int size) {
    buffer = size;
}

static void send(const char* filename, const char* format, ...) {
    mkfifo(filename, 0666);
    int fd = open(filename, O_WRONLY);
    char* text = malloc(buffer * sizeof(char));
    va_list argptr;
    va_start(argptr, format);
    vsprintf(text, format, argptr);
    va_end(argptr);
    write(fd, text, buffer);
    close(fd);
    free(text);
}

static char* recv(const char* filename) {
    mkfifo(filename, 0666);
    int fd = open(filename, O_RDONLY);
    char* text = malloc(buffer * sizeof(char));
    read(fd, text, buffer);
    close(fd);
    return text;
}

static void tlk_write(const char* filename, const char* format, ...) {
    FILE* file = fopen(filename, "w");
    va_list argptr;
    va_start(argptr, format);
    vfprintf(file, format, argptr);
    va_end(argptr);
    fclose(file);
}

static char* tlk_read(const char* filename) {
    FILE* file = fopen(filename, "r");
    char* text = calloc(buffer, sizeof(char));
    fread(text, sizeof(char), buffer, file);
    return text;
}

struct Talk_t {
    void(*setBuffer)(int);
    void(*send)(const char*, const char*, ...);
    char*(*recv)(const char*);
    void(*write)(const char*, const char*, ...);
    char*(*read)(const char*);
} Talk = {
    .setBuffer = setBuffer,
    .send = send,
    .recv = recv,
    .write = tlk_write,
    .read = tlk_read
};

#endif