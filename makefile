CFLAGS=-Wall -Wextra -pedantic -g

SOURCES = pile.c main.c arbre.c

all: $(SOURCES)
	gcc $(CFLAGS) $^ -o main