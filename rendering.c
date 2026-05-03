#define ROWS 40
#define COLS 10
#define CELL 32
#include <SDL2/SDL.h>

#include "board.h"
#include "blockOffsets.h"
#include "piece.h"
#include "hold.h"

void drawBoard(SDL_Renderer *renderer, Board* TetrisBoard) {
	int offset = 20; //top 20 rows are invisible
    for (int i = 0; i < COLS; i++) {
        for (int j = offset; j < ROWS; j++) {
            SDL_Rect rect = {160 + i * CELL, (j - offset) * CELL, CELL, CELL};

            if (TetrisBoard->grid[i][j] > 0) {
                Color bColor = PieceColors[TetrisBoard->grid[i][j]];
                SDL_SetRenderDrawColor(renderer, bColor.r, bColor.g, bColor.b, 255); // use color from piece
                SDL_RenderFillRect(renderer, &rect);
            }

            // grid lines
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void drawPiece(SDL_Renderer *renderer, Piece *TetrisBlock){
	int offset = 20;
    Color bColor = PieceColors[TetrisBlock->blockType];

    for (int i = 0; i < 4; i++){
        int col = TetrisBlock->oriCol + blockRotOffsets[TetrisBlock->blockType][TetrisBlock->rotation][i][0];
        int row = TetrisBlock->oriRow + blockRotOffsets[TetrisBlock->blockType][TetrisBlock->rotation][i][1];
        SDL_Rect rect = {160 + col * CELL, (row - offset) * CELL, CELL, CELL};

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
        SDL_Rect rect = {160 + col * CELL, (row - offset) * CELL, CELL, CELL};

        SDL_SetRenderDrawColor(renderer, bColor.r, bColor.g, bColor.b, 80); // use color from piece
        SDL_RenderFillRect(renderer, &rect);

    }


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

void drawNext(SDL_Renderer *renderer, TTF_Font *font, Piece pieceBucketCurrent[7], Piece pieceBucketNext[7], int currentIndex){
    SDL_Color white = {255, 255, 255};
    SDL_Surface *nextSurface = TTF_RenderText_Solid(font, "NEXT", white);
    SDL_Texture *nextTexture = SDL_CreateTextureFromSurface(renderer, nextSurface);
    SDL_FreeSurface(nextSurface);
    int w, h;
    TTF_SizeText(font, "NEXT", &w, &h);
    SDL_Rect labelRect = {490, 10, w, h};
    SDL_RenderCopy(renderer, nextTexture, NULL, &labelRect);

    for (int n = 0; n < 5; n++) {
    int nextIndex = currentIndex + 1 + n;
    Piece *bucket = pieceBucketCurrent;
    if (nextIndex >= 7) {
        nextIndex -= 7;
        bucket = pieceBucketNext;
    }
    Piece next = bucket[nextIndex];

    Color bColor = PieceColors[next.blockType];
    for (int i = 0; i < 4; i++) {
        int col = blockRotOffsets[next.blockType][0][i][0];
        int row = blockRotOffsets[next.blockType][0][i][1];
        SDL_Rect rect = {490 + col * CELL, 60 + n * 3 * CELL + row * CELL, CELL, CELL};
        SDL_SetRenderDrawColor(renderer, bColor.r, bColor.g, bColor.b, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void drawScore(SDL_Renderer *renderer, TTF_Font *font, int score){
    SDL_Color white = {255, 255, 255};
    SDL_Surface *scoreTextSurface = TTF_RenderText_Solid(font, "SCORE", white);
    SDL_Texture *scoreTextTexture = SDL_CreateTextureFromSurface(renderer, scoreTextSurface);
    SDL_FreeSurface(scoreTextSurface);
    int w, h;
    TTF_SizeText(font, "SCORE", &w, &h);
    SDL_Rect labelRect = {10, 60 + 3*CELL + 10, w, h};
    SDL_RenderCopy(renderer, scoreTextTexture, NULL, &labelRect);

    char scoreStr[20];
    snprintf(scoreStr, sizeof(scoreStr), "%d", score);

    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreStr, white);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);
    int w_2, h_2;
    TTF_SizeText(font, scoreStr, &w_2, &h_2);
    SDL_Rect scoreRect = {10, 60 + 3*CELL + 10 + 24 + 5, w_2/2, h_2/2};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}