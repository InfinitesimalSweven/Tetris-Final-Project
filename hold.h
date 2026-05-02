#ifndef HOLD_H
#define HOLD_H
#include <SDL2/SDL_ttf.h>

typedef struct {
    Piece piece;
    int heldEmpty;
    int hasHeld;
} HoldSlot;

void doHold(Piece *current, HoldSlot *HeldItem);
void drawHold(SDL_Renderer *renderer, HoldSlot *hold, TTF_Font *font);

#endif