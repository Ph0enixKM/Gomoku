#########################
#     Gomoku Makefile   #
#   Author: Paweł Karaś #
# Requirements: GTK+3.0 #
#    Platform: Linux    #
#########################

CC = clang
CFLAGS = -Wall -Wextra -Werror -I . -I include -ferror-limit=1
LFLAGS = -lm 
CGTK = `pkg-config --cflags gtk+-3.0`
LGTK = `pkg-config --libs gtk+-3.0`
NAME = Gomoku
SRC = main.c include/include.c menu/menu.c utils/utils.c lobby/lobby.c talk/talk.c game/game.c game/check.c 

all: $(NAME)
	./$(NAME)

$(NAME): gtkui.o
	$(CC) -std=c11 $(SRC) gtkui.o $(CFLAGS) $(LFLAGS) $(CGTK) $(LGTK) -o $(NAME)
	
gtkui.o:
	$(CC) -c gtkui/gtkui.c -o gtkui.o $(CFLAGS) $(CGTK)

clean:
	rm gtkui.o
	rm $(NAME)


