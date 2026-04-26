#include <stdio.h>
#include "blockOffsets.h"
#include "board.h"

typedef enum {
    EMPTY, LIGHT_BLUE, DARK_BLUE, ORANGE, YELLOW, GREEN, RED, MAGENTA
} BlockColor;
typedef enum {
    EMPTY, I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, Z_BLOCK, T_BLOCK
} BlockType;
//These enumerations both corrospond with each other, so each block type has their correct color type.
//Seperated the enumerations just in case block colors wanted to be changed in the future.


typedef struct {
    int blockCords[4][2]; //Origin cord defined at [0][2]
    int rotation; //Rotation states-> 0 origin, 1 is 90 degrees, 2 is 180 degrees, and 3 is 270 degrees 
    BlockType letter;
    ColorType color;
} Piece

//spawns piece at appropriate location. (We choose coordinate system (0,0) as top-left)
//We use a 40x10 board. Why? Idk the tetris requirements told me to. We really only need 10x24...
Piece createPiece(BlockType letter, ColorType color){
    Piece tetrisBlock = {.rotation = 0, .letter = letter, .color = color}
    memcpy(tetrisBlock.blockCords, spawnPos[letter], sizeof(tetrisBlock.blockCords));
    return tetrisBlock;
}

bool checkCollision(Piece TetrisBlock, int dx, int dy, Board* Board) {
    for (int i = 0; i < 4; i++) {
        TetrisBlock.blockCords[i][0] += dx;
        TetrisBlock.blockCords[i][1] += dy;

        if (TetrisBlock.blockCords[i][0] >= 10 ||
            TetrisBlock.blockCords[i][1] >= 40){
                return true;
        }


        if (TetrisBlock.blockCords[i][0] < 0 ||
            TetrisBlock.blockCords[i][1] < 0){
                return true;
        }

        if (Board->grid[TetrisBlock.blockCords[i][1]][TetrisBlock.blockCords[i][0]] > 0){
                return true;
            }
        }
    return false;
}


void translatePiece(Piece* tetrisBlock, int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        TetrisBlock->blockCords[i][0] += dx;
        TetrisBlock->blockCords[i][1] += dy;
    }
}

void transCollision(Piece* TetrisBlock, int dx, int dy, Board* Board){

    if (!checkCollision(*TetrisBlock, dx, dy, Board))
        translatePiece(TetrisBlock, dx, dy);

}

void rotCollision(Piece* TetrisBlock, int dx, int dy, Board* Board){

}


//I want to implement a binary search tree becuase its technically more efficient but
//its ok readable code is more important methinks, maybe ill comment a binTree version
//and ask kyle what he thinks

#define collisionInusrance
int hardDropPiece(Piece* TetrisBlock, Board* Board){

    for(int i = 0; i < 25; i++){
        checkCollision(TetrisBlock, 0, -i, Board);
    }

    return i;
}


