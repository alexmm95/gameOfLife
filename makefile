all: game_of_life

game_of_life: main.o mundo.o
	gcc main.o mundo.o -o game_of_life

main.o: main.c mundo.h
	gcc -c main.c

mundo.o: mundo.h mundo.c
	gcc -c mundo.c
