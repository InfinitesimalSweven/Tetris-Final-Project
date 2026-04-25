#include <stdio.h>
#include "blockOffsets.h"

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

//void rotatePiece(){}

void translatePieceDown(){}

void translatePieceRight(){}

void translatePieceLeft(){}

void hardDropPiece(){}


