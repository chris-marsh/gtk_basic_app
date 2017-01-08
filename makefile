CC=gcc
CFLAGS=-std=c99 -g -Wall 
GTKFLAGS=`pkg-config --cflags --libs gtk+-3.0`
GTKLIBS=`pkg-config --cflags --libs gtk+-3.0`
 
SOURCE = src/main.c src/gui.c src/config.c src/common.c
EXEC = basic

$(EXEC): $(SOURCE)
	$(CC) $(SOURCE) -o $(EXEC) $(CFLAGS) $(GTKFLAGS) -I ./include

.PHONY: clean
clean:
	rm -f basic
