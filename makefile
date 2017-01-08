CC=gcc
CFLAGS=-std=c99 -g -Wall 
GTKFLAGS=`pkg-config --cflags --libs gtk+-3.0`
GTKLIBS=`pkg-config --cflags --libs gtk+-3.0`
 
SOURCE = main.c gui.c config.c common.c
EXEC = basic

$(EXEC): $(SOURCE)
	$(CC) $(SOURCE) -o $(EXEC) $(CFLAGS) $(GTKFLAGS) -g

.PHONY: clean
clean:
	rm -f basic
