CC=clang

all: main
	dist/main

main: main.o
	${CC} dist/main.o -o dist/main `pkg-config --cflags gtk+-3.0`

# uik.o:
# 	${CC} -c src/uik/uik.c -o dist/uik.o `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`

main.o:
	${CC} -c src/main.c -o dist/main.o `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`
