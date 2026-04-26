CC = gcc
CFLAGS = -Wall `sdl2-config --cflags`
LIBS = `sdl2-config --libs`

tetris: main.o board.o piece.o blockOffsets.o
	$(CC) -o tetris main.o board.o piece.o blockOffsets.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

board.o: board.c
	$(CC) $(CFLAGS) -c board.c

piece.o: piece.c
	$(CC) $(CFLAGS) -c piece.c

blockOffsets.o: blockOffsets.c
	$(CC) $(CFLAGS) -c blockOffsets.c

clean:
	rm -f *.o tetris