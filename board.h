#ifndef BOARD_H
#define BOARD_H
#define ROWS 40
#define COLS 10
#define CELL 32

#include <SDL2/SDL.h>

typedef struct {
    int grid[COLS][ROWS];
    int score;
    int level;
} Board;

void drawBoard(SDL_Renderer *renderer, Board* TetrisBoard);
Board createBoard(int score, int level);
void checkAndClearLine(Board* TetrisBoard, int yLow, int yHigh);
int isGameEnd(Board* TetrisBoard);
#endif
