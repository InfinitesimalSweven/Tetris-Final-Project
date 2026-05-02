#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "board.h"
#include "piece.h"
#include "hold.h"

//https://tetris.wiki/Tetris_Guideline
//TODO: Kyle read the guidelines for the project!
int const WIDTH = 640;
int const HEIGHT = 640;
int main(){

    //Block initilizes the SDL engine. SDL Init says we want ot use video, then we create a centered tetris window, and render it.
	SDL_Init(SDL_INIT_VIDEO); //SDL_Init(SDL_INIT_AUDIO); Include only if we want to code in sound
	SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //-1 just uses best case!
	TTF_Font *font = TTF_OpenFont("PressStart2P-Regular", 24);

	int running = 1;
	int gravTimer = 800;
	int lastFall = SDL_GetTicks();
	
	Board board = createBoard(0, 0);
	HoldSlot hold = {.piece = createPiece(EMPTY), .heldEmpty = 1, .hasHeld = 0};
	Piece pieceBucket[7];
	createPieceBucket(pieceBucket);
	int bucketIndex = 0;
	Piece piece = pieceBucket[bucketIndex];	//TODO; Tommorow make Tetris bag (contains 7 pieces so you dont have repeats, this randomly defines the type of block)
	
	
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = 0;
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						transCollision(&piece, &board, -1, 0);
						break;
					case SDLK_RIGHT:
						transCollision(&piece, &board,  1, 0);
						break;
					case SDLK_DOWN:
						transCollision(&piece, &board,  0, 1);
						break;
					case SDLK_UP:
					case SDLK_x:
						rotCollision(&piece, &board, 1);
						break;
					case SDLK_z:
						rotCollision(&piece, &board, -1);
						break;
					case SDLK_c:
						doHold(&piece, &hold);
						break;
					case SDLK_SPACE:
						hardDropPiece(&piece, &board);
						placePiece(&piece, &board);
						checkAndClearLine(&board, 0, ROWS - 1);
						bucketIndex++;
						if (bucketIndex>=7){
							createPieceBucket(pieceBucket);
							bucketIndex = 0;
						}
						piece = pieceBucket[bucketIndex];
						break;
				}
			}
		}
		
		if (SDL_GetTicks() - lastFall > gravTimer) {
			if(!transCollision(&piece, &board, 0, 1)){
				placePiece(&piece, &board);
				checkAndClearLine(&board, 0, ROWS - 1);
				bucketIndex++;
				if (bucketIndex >= 7) {
					createPieceBucket(pieceBucket);
					bucketIndex = 0;
				}
				piece = pieceBucket[bucketIndex];
			}
			lastFall = SDL_GetTicks();
		}

		//Render
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		

		drawPiece(renderer, &piece);
		drawBoard(renderer, &board);
		drawGhostPiece(renderer, &board, &piece);
		drawHold(renderer, &hold, font);

		
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
