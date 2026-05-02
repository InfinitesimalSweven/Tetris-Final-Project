#include "piece.h"
#include "board.h"
#include "hold.h"
#include "blockOffsets.h"

//Puts held in if piece is empty. If piece was held last turn locks the system. If there is a piece swaps the pieces.
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

//DrawHold draws the hold yay (I hate SDL none of this makes sense what the heck)
void drawHold(SDL_Renderer *renderer, HoldSlot *hold, TTF_Font *font){
    SDL_Color white = {255, 255, 255};
    SDL_Surface *holdSurface = TTF_RenderText_Solid(font, "HOLD", white);
    SDL_Texture *holdTexture = SDL_CreateTextureFromSurface(renderer, holdSurface);
    SDL_FreeSurface(holdSurface);
    int w, h;
    TTF_SizeText(font, "HOLD", &w, &h);
    SDL_Rect labelRect = {10, 10, w, h};
    SDL_RenderCopy(renderer, holdTexture, NULL, &labelRect);



    if (!hold->heldEmpty){
        Color bColor = PieceColors[hold->piece.blockType];

        for (int i = 0; i < 4; i++){
            int col = blockRotOffsets[hold->piece.blockType][0][i][0];
            int row = blockRotOffsets[hold->piece.blockType][0][i][1];
            SDL_Rect rect = {10 + col * CELL, 60 + row * CELL, CELL, CELL};

            SDL_SetRenderDrawColor(renderer, bColor.r, bColor.g, bColor.b, 255); // use color from piece
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &rect);

        }
    }

}

