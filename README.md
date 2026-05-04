# Tetris-Final-Project
Using C, we have recreated Tetris, the #1 best selling game with 520 million sales. To recreate Tetris, we heavily relied on


## Methods
This project was built following [The Tetris Guideline](tetris.wiki/Tetris_Guideline)

### Basics
First, we needed to address the actual board the game is played on. To achieve this, a Board struct was created in board.h
```
typedef struct {
    int grid[COLS][ROWS];
    int score;
    int level;
} Board;
```
This struct contains a 2D array, where the game is actually played on. Following The Tetris Guideline, there will be 10 columns and 40 rows, with only the bottom 20 rows being displayed. The Board struct also contains a score and a level integer, which is self-explanatory but will be explained later on.  
There is a simple createBoard function that just creates a blank board.  
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

