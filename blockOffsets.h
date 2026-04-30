#ifndef BLOCKOFFSETS_H
#define BLOCKOFFSETS_H

#define BLOCKTYPES 8
#define BLOCKCORDS 4
#define CORDS 2
#define ROTATIONS 4
#define TESTS 5

extern const int spawnPos[BLOCKTYPES][CORDS];
extern const int blockRotOffsets[BLOCKTYPES][ROTATIONS][BLOCKCORDS][CORDS];
extern const int rotTestI[ROTATIONS*2][TESTS][CORDS];
extern const int rotTestJLSTZ[ROTATIONS*2][TESTS][CORDS];

#endif