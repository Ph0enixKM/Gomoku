clang src/main.c src/gtk-ui/gtkui.c -I src/gtk-ui -o dist/main `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -xc -Wall -Wextra
\cp -r public -t dist
dist/main $@
