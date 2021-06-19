# Makefile

CC=g++

all:snakegame

snakegame: GateNWall.o Item.o Map.o Score.o Snake.o main.o
	$(CC) -g -o snakegame GateNWall.o Item.o Map.o Score.o Snake.o main.o -lncurses -pthread -std=c++17

GateNWall.o: GateNWall.cpp GateNWall.h
	$(CC) -g -c GateNWall.cpp

Item.o: Item.cpp Item.h
	$(CC) -g -c Item.cpp

Map.o: Map.cpp Map.h
	$(CC) -g -c Map.cpp

main.o: main.cpp 
	$(CC) -g -c main.cpp -lncurses -pthread -std=c++17

Score.o: Score.cpp Score.h
	$(CC) -g -c Score.cpp

Snake.o: Snake.cpp Snake.h
	$(CC) -g -c Snake.cpp

clean:
	rm -rf *.o