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


void drawBoard(SDL_Renderer *renderer, Board* TetrisBoard) {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            SDL_Rect rect = {i * CELL, j * CELL, CELL, CELL};

            if (TetrisBoard->grid[i][j] > 0) {
                Color bColor = PieceColors[TetrisBoard->grid[i][j]];
                SDL_SetRenderDrawColor(renderer, bColor.r, bColor.g, bColor.b, 255); // use color from piece
                SDL_RenderFillRect(renderer, &rect);
            }

            // grid lines
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
