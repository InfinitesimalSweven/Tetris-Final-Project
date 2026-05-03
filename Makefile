CC = gcc
CFLAGS = -Wall `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_ttf

tetris: main.o board.o piece.o blockOffsets.o hold.o rendering.o
	$(CC) -o tetris main.o board.o piece.o blockOffsets.o hold.o rendering.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

board.o: board.c
	$(CC) $(CFLAGS) -c board.c

piece.o: piece.c
	$(CC) $(CFLAGS) -c piece.c

blockOffsets.o: blockOffsets.c
	$(CC) $(CFLAGS) -c blockOffsets.c

hold.o: hold.c
	$(CC) $(CFLAGS) -c hold.c

rendering.o: rendering.c
	$(CC) $(CFLAGS) -c rendering.c

clean:
	rm -f *.o tetris