#ifndef PIECE_H
#define PIECE_H

#include <SDL2/SDL.h>
#include "board.h"

typedef struct {
    Uint8 r, g, b;
} Color;

typedef enum {
    EMPTY, I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, Z_BLOCK, T_BLOCK
} BlockType;

typedef struct {
    int oriCol;
    int oriRow;
    int rotation;
    BlockType blockType;
} Piece;

extern const Color PieceColors[8];

Piece createPiece(BlockType blockType);
int checkCollision(Piece* TetrisBlock, Board* Board, int dx, int dy, int drot);
int transCollision(Piece* TetrisBlock, Board* Board, int dx, int dy);
int rotCollision(Piece* TetrisBlock, Board* Board, int drot);
void hardDropPiece(Piece* TetrisBlock, Board* Board);
void placePiece(Piece* TetrisBlock, Board* Board);
void drawPiece(SDL_Renderer *renderer, Piece *TetrisBlock);
void drawGhostPiece(SDL_Renderer *renderer, Board* Board, Piece *TetrisBlock);

#endif