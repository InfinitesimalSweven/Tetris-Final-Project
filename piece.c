#include <stdio.h>


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
    BlockType type;
    ColorType color;
} Piece

Piece createPiece(){}

Piece rotatePiece(){}

Piece translatePiece(){}


