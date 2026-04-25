#include <stdio.h>
#define ROWS 20
#define COLS 10


//This file will be expanded to create checker files.

//Originally the plan was the grid was going to contain 1's for filled in and 0 for not filled in.
//However, it might be better to assign each color a number, and if number > 0 its filled in.
//Define each color and assign it to a number. Then we can use colors as numbers! 
typedef struct {
    int grid[ROWS][COLS];
    int score;
    int level;
} Board;

Board createBoard(int score, int level){
    Board tetrisBoard = {.score = score, .level = level};
    return tetrisBoard;
}
