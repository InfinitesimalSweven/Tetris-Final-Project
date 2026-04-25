//There are two ways to rotate a tetris block, which is using block offsets, or by rotating 
//it around the centroid. Dealing with rotating a centroid and having to deal with all that 
//is not worth. The other option seems to be hardcoded block offsets which is what this file is. 
#define BLOCKTYPES 7
#define BLOCKCORDS 4
#define CORDS 2
#define ROTATIONS 4

int spawnPos[BLOCKTYPES][BLOCKCORDS][CORDS]{ //7, 4, 2
    {{18,3},{18,4},{18,5},{18,6}}, // I
    {{17,3},{18,3},{18,4},{18,5}}, // J
    {{17,5},{18,3},{18,4},{18,5}}, // L
    {{18,4},{18,5},{19,4},{19,5}}, // O
    {{17,4},{17,5},{18,3},{18,4}}, // S
    {{17,3},{17,4},{18,4},{18,5}}, // Z
    {{17,4},{18,3},{18,4},{18,5}}, // T
}

