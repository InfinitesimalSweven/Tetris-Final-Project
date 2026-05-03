#include "piece.h"

#define ROWS 40
#define COLS 10
#define CELL 32


//This file will be expanded to create checker files.

//Originally the plan was the grid was going to contain 1's for filled in and 0 for not filled in.
//However, it might be better to assign each color a number, and if number > 0 its filled in.
//Define each color and assign it to a number. Then we can use colors as numbers!


Board createBoard(int score, int level){
    Board TetrisBoard = {0};
    TetrisBoard.score = score;
    TetrisBoard.level = level;
    return TetrisBoard;
}

void checkAndClearLine(Board* TetrisBoard, int yLow, int yHigh){

    int isFull;
    for (int y = yHigh; y >= yLow; y--){
        isFull = 1;
        for (int x = 0; x < COLS; x++){
            if (TetrisBoard->grid[x][y] == 0){
                isFull = 0;
                break;
            }
        }

        if (isFull){
            for (int i = y; i > 0; i--){
                for (int x = 0; x < COLS; x++){
                    TetrisBoard->grid[x][i] = TetrisBoard->grid[x][i-1];
                }
            }
            for (int x = 0; x < COLS; x++){
                TetrisBoard->grid[x][0] = 0;
            }
            y++; // re-check same row since lines shifted down
        }
    }
}

int isGameEnd(Board* TetrisBoard){
    for (int x = 0; x < COLS; x++){
                if (TetrisBoard->grid[x][19] == 1)
                    return 1;
    }
    return 0;
}