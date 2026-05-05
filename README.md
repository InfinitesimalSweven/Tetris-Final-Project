# Tetris-Final-Project
Using C, we have recreated Tetris, the #1 best selling game with 520 million sales. To recreate Tetris, we heavily relied on


## Methods
This project was built following [The Tetris Guideline](https://tetris.wiki/Tetris_Guideline)

### Board
First, we needed to address the actual board the game is played on. To achieve this, a Board struct was created in board.h
```
typedef struct {
    int grid[COLS][ROWS];
    int score;
    int level;
} Board;
```
This struct contains a 2D array, where the game is actually played on. Following [The Tetris Guideline](https://tetris.wiki/Tetris_Guideline), there will be 10 columns and 40 rows, with only the bottom 20 rows being displayed. The Board struct also contains a score and a level integer, which is self-explanatory but will be explained later on.  
There is a simple createBoard function that just creates a blank board.  

To clear filled lines, we have the `int checkAndClearLine(Board* TetrisBoard, int yLow, int yHigh)` function.
```
int checkAndClearLine(Board* TetrisBoard, int yLow, int yHigh){

    int isFull;
    int linesCleared = 0;
    for (int y = yHigh; y >= yLow; y--){
        isFull = 1;
        for (int x = 0; x < COLS; x++){
            if (TetrisBoard->grid[x][y] == 0){
                isFull = 0;
                break;
            }
        }

        if (isFull){
            linesCleared++;
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
    return linesCleared;
}
```
The function searches through the rows bottom up, stopping when there is a row that is NOT filled. Then, it shifts rows down, taking the color from each cell above and putting it into the current cell. The top row is cleared with 0's and 

### Pieces  
As we did with the board, we must also create a Piece struct in piece.h  
```
typdef struct {
    int oriCol;
    int oriRow;
    Rotation rotation;
    Blocktype blockType;
} Piece;
```
Both oriCol and oriRow store the location of the piece. Instead of using an basic integer to hold rotation and blockType values, we instead defined enumerators to ease readability of the code.
```
typedef enum {
    EMPTY, I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, Z_BLOCK, T_BLOCK
} BlockType;

typedef enum {
    ROT_0, ROT_R, ROT_2, ROT_L
} Rotation;
```
blah blah blah



### Display & Input
As stated previously, we used Simple DirectMedia Layer 2 (SDL2) to display the game and record inputs from the player
