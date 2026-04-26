#include <stdio.h>
#include <SDL2/SDL.h>
#include "board.h"
#include "piece.h"

//https://tetris.wiki/Tetris_Guideline
//TODO: Kyle read the guidelines for the project!

int main(){
/*
    //Block initilizes the SDL engine. SDL Init says we want ot use video, then we create a centered tetris window, and render it.
    SDL_Init(SDL_INIT_VIDEO); //SDL_Init(SDL_INIT_AUDIO); Include only if we want to code in sound
    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //-1 just uses best case!

    
    int lastFall = SDL_GetTicks();
    int gravTimer = 800;
    
    Board TetrisBoard = createBoard(0, 0);
    Piece TetrisPiece = createPiece(0); //TODO; Tommorow make Tetris bag (contains 7 pieces so you dont have repeats, this randomly defines the type of block)

    while (running) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    
    if (event.type == SDL_QUIT) running = 0;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:  transCollision(&piece, &board, -1, 0); break;
            case SDLK_RIGHT: transCollision(&piece, &board,  1, 0); break;
            case SDLK_DOWN:  transCollision(&piece, &board,  0, 1); break;
            case SDLK_UP:    rotCollision(&piece, &board);          break;
            case SDLK_SPACE: hardDropPiece(&piece, &board);         break;
        }
    }
}

        // in game loop:
        if (SDL_GetTicks() - lastFall > gravTimer) {
            transCollision(&piece, &board, 0, 1);
            lastFall = SDL_GetTicks();
        }
        

        SDL_RenderClear(renderer);
        draw_board(renderer, &board);
        draw_piece(renderer, &current);
        draw_ghost_piece(renderer, &current, &board);
        SDL_RenderPresent(renderer);
    
        SDL_Delay(16); 
    }

*/
}
