#include <stdio.h>
#include <assert.h>

#include "blockOffsets.h"
#include "board.h"
#include "piece.h"
#define CELL 32



//These enumerations both corrospond with each other, so each block type has their correct color type.
//Seperated the enumerations just in case block colors wanted to be changed in the future.

const Color PieceColors[8] = {
    {0,   0  , 0  }, // EMPTY
    {0,   255, 255}, // I - light_blue
    {0,   0,   255}, // J - dark_blue
    {255, 165, 0  }, // L - orange
    {255, 255, 0  }, // O - yellow
    {0,   255, 0  }, // S - green
    {255, 0,   0  }, // Z - red
    {128, 0,   128}, // T - magenta
};

//spawns piece at appropriate location. (We choose coordinate system (0,0) as top-left)
//We use a 40x10 board. Why? Idk the tetris requirements told me to. We really only need 10x24...
Piece createPiece(BlockType blockType){
    Piece TetrisBlock = {.oriCol = spawnPos[blockType][0], .oriRow = spawnPos[blockType][1], .rotation = 0, .blockType = blockType};
    return TetrisBlock;
}

int checkCollision(Piece* TetrisBlock, Board* Board, int dx, int dy, int drot) {

    int col = TetrisBlock->oriCol + dx;
    int row = TetrisBlock->oriRow + dy;
    Rotation rot = (TetrisBlock->rotation + drot + 4) % 4;

    for (int i = 0; i < 4; i++) {
        int rowOff = row + blockRotOffsets[TetrisBlock->blockType][rot][i][0];
        int colOff = col + blockRotOffsets[TetrisBlock->blockType][rot][i][1];

        if (colOff >= 10 || rowOff >= 40) return 1;

        if (colOff < 0 || rowOff < 0) return 1;

        if (Board->grid[colOff][rowOff] > 0) return 1;
    }

    return 0;
}


int transCollision(Piece* TetrisBlock, Board* Board, int dx, int dy){

    if (!checkCollision(TetrisBlock, Board, dx, dy, 0)){
        TetrisBlock->oriCol += dx;
        TetrisBlock->oriRow += dy;
        return 1;
    }

    return 0;

}

//when using this function never rotate more than 1 states (always input 1 or -1).
//This is because rotation tests only work for 1 step rotations
//Also the only time you'd wanna go more than 1 rotation is just when there are two
//succesive inputs...just call the function twice!

int rotCollision(Piece* TetrisBlock, Board* Board, int drot){
        assert(drot == 1 || drot == -1); // only single-step rotations supported for this function
        
        int rotIndex;
        Rotation rot = TetrisBlock->rotation;

        if (drot == 1)
            rotIndex = (2 * rot) % 8;

        if (drot == -1)
            rotIndex = (2 * rot - 1 + 8) % 8;

        if (TetrisBlock->blockType == I_BLOCK){
            for (int test = 0; test < 5; test++){
                TetrisBlock->oriCol += rotTestI[rotIndex][test][0];
                TetrisBlock->oriRow += rotTestI[rotIndex][test][1];

                if (!checkCollision(TetrisBlock, Board, 0, 0, drot)){
                    TetrisBlock->rotation = (TetrisBlock->rotation + drot + 4) % 4;
                    return 1; //successful rotation!
                }

                TetrisBlock->oriCol -= rotTestI[rotIndex][test][0];
                TetrisBlock->oriRow -= rotTestI[rotIndex][test][1];
            }
        }

        else {
            for (int test = 0; test < 5; test++){
                TetrisBlock->oriCol += rotTestJLSTZ[test][rotIndex][0];
                TetrisBlock->oriRow += rotTestJLSTZ[test][rotIndex][1];

                if (!checkCollision(TetrisBlock, Board, 0, 0, drot)){
                    TetrisBlock->rotation = (TetrisBlock->rotation + drot + 4) % 4;
                    return 1; //successful rotation!
                }

                TetrisBlock->oriCol -= rotTestJLSTZ[test][rotIndex][0];
                TetrisBlock->oriRow -= rotTestJLSTZ[test][rotIndex][1];
        }
    }

    return 0; //unsuccesful rotation :(
}

void hardDropPiece(Piece* TetrisBlock, Board* Board){
    int displacement;
    for(displacement = 1; displacement < 40; displacement++){
        if (checkCollision(TetrisBlock, Board, 0, displacement, 0))
            break;
    }

    transCollision(TetrisBlock, Board, 0, displacement-1);
}

//Places piece on to the board
void placePiece(Piece* TetrisBlock, Board* Board){

    for (int i = 0; i < 4; i++){
        Board->grid[TetrisBlock->oriCol + blockRotOffsets[TetrisBlock->blockType][TetrisBlock->rotation][i][0]][TetrisBlock->oriRow + blockRotOffsets[TetrisBlock->blockType][TetrisBlock->rotation][i][1]] = TetrisBlock->blockType;
    }

}

void drawPiece(SDL_Renderer *renderer, Piece *TetrisBlock){
	int offset = 20;
    Color bColor = PieceColors[TetrisBlock->blockType];

    for (int i = 0; i < 4; i++){
        int col = TetrisBlock->oriCol + blockRotOffsets[TetrisBlock->blockType][TetrisBlock->rotation][i][0];
        int row = TetrisBlock->oriRow + blockRotOffsets[TetrisBlock->blockType][TetrisBlock->rotation][i][1];
        SDL_Rect rect = {col * CELL, (row - offset) * CELL, CELL, CELL};

        SDL_SetRenderDrawColor(renderer, bColor.r, bColor.g, bColor.b, 255); // use color from piece
        SDL_RenderFillRect(renderer, &rect);

    }
}

//This piece is the indicator piece that tells you where you will place your piece!
//Basically just the drawPiece function but with reduced opacity
//Made the function seperate for clarity
void drawGhostPiece(SDL_Renderer *renderer, Board* Board, Piece *TetrisBlock){
	int offset = 20;
    Color bColor = PieceColors[TetrisBlock->blockType];

    int displacement;
    for(displacement = 1; displacement < 25; displacement++){
        if (checkCollision(TetrisBlock, Board, 0, displacement, 0))
            break;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < 4; i++){
        int col = TetrisBlock->oriCol + blockRotOffsets[TetrisBlock->blockType][TetrisBlock->rotation][i][0];
        int row = TetrisBlock->oriRow + blockRotOffsets[TetrisBlock->blockType][TetrisBlock->rotation][i][1];
        row = row + displacement - 1;
        SDL_Rect rect = {col * CELL, (row - offset) * CELL, CELL, CELL};

        SDL_SetRenderDrawColor(renderer, bColor.r, bColor.g, bColor.b, 80); // use color from piece
        SDL_RenderFillRect(renderer, &rect);

    }


}


