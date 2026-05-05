# Tetris in C
We have recreated Tetris, the #1 best selling video game with over 520 million sales, in C. Aside from the standard C libraries, we also used the [Simple DirectMedia Layer 2 (SDL2)](https://wiki.libsdl.org/SDL2/Introduction) library to render the game and capture inputs from the player. This project was built following the official [Tetris Guideline](https://tetris.wiki/Tetris_Guideline)

- [Method](#Board)
- [Installation](#Installation)
## Method
### Board
First, we needed to address the actual board the game is played on. To achieve this, a Board struct was created in board.h
```c
typedef struct {
    int grid[COLS][ROWS];
    int score;
    int level;
} Board;
```
This struct contains a 2D array, where the game is actually played on. Following [The Tetris Guideline](https://tetris.wiki/Tetris_Guideline), there will be 10 columns and 40 rows, with only the bottom 20 rows being displayed. The Board struct also contains a score and a level integer, which is self-explanatory but will be explained later on.  
There is a simple createBoard function that just creates a blank board.  

To clear filled lines, we have the `int checkAndClearLine(Board* TetrisBoard, int yLow, int yHigh)` function.
```c
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
The function searches through the rows bottom up, stopping when there is a row that is NOT filled. Then, it shifts rows down, taking the color from each cell above and putting it into the current cell. The top row is cleared with 0's and the row is rechecked

`int isGameEnd(Board* TetrisBoard){}` just checks a specific row for any filled cells. If filled, will return a 1, which prompts a game end.

### The Bag
According to the Tetris Guideline, pieces are pulled out of a bag containing 1 of each unique piece. When the bag is empty, a new bag is created and shuffled to minimize "unlucky events."
```c
void createPieceBucket(Piece pieceBucket7[7]) {
    int indices[7] = {1, 2, 3, 4, 5, 6, 7};

    // Implemented fisher-yates shuffle
    for (int i = 6; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    for (int i = 0; i < 7; i++) {
        pieceBucket7[i] = createPiece(indices[i]);
    }
}
```
To implement this, we used an array storing integers from 1 through 7, which represents each of the 7 possible pieces, and randomized the order using a fisher-yates shuffle.

### Pieces  
As we did with the board, we must also create a Piece struct in piece.h  
```c
typdef struct {
    int oriCol;
    int oriRow;
    Rotation rotation;
    Blocktype blockType;
} Piece;
```
Both oriCol and oriRow store the location of the piece. Instead of using an basic integer to hold rotation and blockType values, we instead defined enumerators to ease readability of the code.
```c
typedef enum {
    EMPTY, I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, Z_BLOCK, T_BLOCK
} BlockType;

typedef enum {
    ROT_0, ROT_R, ROT_2, ROT_L
} Rotation;
```

To implement the rotations found in Tetris, we could have:
1. Used complex math to rotate the blocks around a central centroid point.
2. Hardcoded the exact coordinates for every piece in every possible rotation state.

We chose the second option for efficiency and simplicity, which is stored in `blockOffsets.c`.

Instead of actively calculating rotations, `blockOffsets.c` stores all possible states in the 4-dimensional array:
`const int blockRotOffsets[BLOCKTYPES][ROTATIONS][BLOCKCORDS][CORDS];`

Following the Super Rotation System (SRS) in [The Tetris Guideline](https://tetris.wiki/Tetris_Guideline), `blockOffsets.c` also contains the `rotTestI` and `rotTestJLSTZ` arrays. If a piece tries to rotate but hits a wall or another block, these arrays provide the 5 "wall kick" fallback tests to shift the piece slightly (up, down, left, or right).

### The Hold Mechanic
To allow players to save a piece for later, we created a HoldSlot structure 
```c
typedef struct {
    Piece piece;
    int heldEmpty;
    int hasHeld;
} HoldSlot; 

void doHold(Piece *current, HoldSlot *HeldItem){
    if (HeldItem->hasHeld) return;
    else if (HeldItem->heldEmpty){
        HeldItem->piece = *current;
        HeldItem->heldEmpty = 0;

    }
    else{
        Piece temp = HeldItem->piece;
        HeldItem->piece = *current;
        *current = temp;
    }
    HeldItem->hasHeld = 1;
}
```
The HoldSlot struct keeps track of the held piece. In order to prevent infinite swapping, it also has a hasHeld integer, which acts as a boolean and will prevent further swaps in doHold.


### Display & Input
As stated previously, we used Simple DirectMedia Layer 2 (SDL2) to display the game and record inputs from the player
All the functions just render the stuff on screen. Will expand on this if Hong says so.

### main.c (Game Loop etc)
First, we initialize everything and start the game. A lot of these settings are adjustable, such as `int gravTimer` which dictates the speed at which pieces fall. The game loop is basically just checking for any inputs. If there are no inputs, it checks if the time since the last fall has exceeded that of the set `gravTimer`

If so, it drops the piece by one and checks for any collisions, places piece if applicable, and clears lines if applicable. Lastly, the frames are rendered again.

(Will probably expand this but I think it is good enough for now, we can just go through the code manually during presentation)


## Installation
### Dependencies
- gcc
- [Simple DirectMedia Layer 2 (SDL2)](https://wiki.libsdl.org/SDL2/Introduction)
    - sudo apt install libsdl2-dev
- SDL2 TrueType Font extension
    - sudo apt install libsdl2-ttf-dev

### How To Run
```
make  
./tetris  
```
