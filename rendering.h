#ifndef RENDERING_H
#define RENDERING_H
#include <SDL2/SDL_ttf.h>

void drawHold(SDL_Renderer *renderer, HoldSlot *hold, TTF_Font *font);
void drawPiece(SDL_Renderer *renderer, Piece *TetrisBlock);
void drawGhostPiece(SDL_Renderer *renderer, Board* Board, Piece *TetrisBlock);
void drawBoard(SDL_Renderer *renderer, Board* TetrisBoard);
void drawNext(SDL_Renderer *renderer, TTF_Font *font, Piece pieceBucketCurrent[7], Piece pieceBucketNext[7], int currentIndex);
void drawScore(SDL_Renderer *renderer, TTF_Font *font, int score);
#endif