#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "board.h"
#include "piece.h"
#include "hold.h"
#include "rendering.h"

int const WIDTH = 640;
int const HEIGHT = 640;

int main(){

	//Initializes SDL Engine and prepares it for display
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //-1 uses best available
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("PressStart2P-Regular.ttf", 24);

	//Initial Variables and Such
	int running = 1;
	int gravTimer = 800;
	int lockDelay = 500;
	int lastLand = -1;
	int score = 0;
	int lastFall = SDL_GetTicks();
	Board board = createBoard(0, 0);
	HoldSlot hold = {.piece = createPiece(EMPTY), .heldEmpty = 1, .hasHeld = 0};
	Piece pieceBucketCurrent[7];
	Piece pieceBucketNext[7];
	createPieceBucket(pieceBucketCurrent);
	createPieceBucket(pieceBucketNext);
	int bucketIndex = 0;
	Piece piece = pieceBucketCurrent[bucketIndex];

	//Game Loop
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
						if (transCollision(&piece, &board, 0, 1))
        					score += 1;
    					break;
					case SDLK_UP:
					case SDLK_x:
						if (rotCollision(&piece, &board, 1))
       						lastLand = -1;
    					break;
					case SDLK_z:
						if (rotCollision(&piece, &board, -1))
       						lastLand = -1;
    					break;
					case SDLK_c:
						if (hold.heldEmpty) {
							doHold(&piece, &hold);
							bucketIndex++;
							if (bucketIndex >= 7) {
								memcpy(pieceBucketCurrent, pieceBucketNext, sizeof(pieceBucketNext));
								createPieceBucket(pieceBucketNext);
								bucketIndex = 0;
							}
							piece = pieceBucketCurrent[bucketIndex];
							hold.hasHeld = 1;
						} else {
							doHold(&piece, &hold);
						}
						break;
					case SDLK_SPACE:
						if (event.key.repeat == 0) {
							int cellsDropped = hardDropPiece(&piece, &board);
							placePiece(&piece, &board);
							int linesCleared = checkAndClearLine(&board, 0, ROWS - 1);
							switch (linesCleared) {
								case 1: score += 100; break;
								case 2: score += 300; break;
								case 3: score += 500; break;
								case 4: score += 800; break;
							}
							bucketIndex++;
							score += 2 * cellsDropped;
							if (bucketIndex >= 7) {
								memcpy(pieceBucketCurrent, pieceBucketNext, sizeof(pieceBucketNext));
								createPieceBucket(pieceBucketNext);
								bucketIndex = 0;
							}
							piece = pieceBucketCurrent[bucketIndex];
							hold.hasHeld = 0;
						}
						break;
				}
			}
		}

		//Idle Fall Loop
		if (SDL_GetTicks() - lastFall > gravTimer) {
			transCollision(&piece, &board, 0, 1);
			lastFall = SDL_GetTicks();
		}

		//Checks for piece landing
		if(checkCollision(&piece, &board, 0, 1, 0)) {
			if (lastLand == -1)
				lastLand = SDL_GetTicks();
			if (SDL_GetTicks() - lastLand > lockDelay){
				placePiece(&piece, &board);
				int linesCleared = checkAndClearLine(&board, 0, ROWS - 1);
				switch (linesCleared) {
					case 1: score += 100; break;
					case 2: score += 300; break;
					case 3: score += 500; break;
					case 4: score += 800; break;
				}
				bucketIndex++;
        		if (bucketIndex >= 7) {
					memcpy(pieceBucketCurrent, pieceBucketNext, sizeof(pieceBucketNext));
					createPieceBucket(pieceBucketNext);
					bucketIndex = 0;
				}
				piece = pieceBucketCurrent[bucketIndex];
        		hold.hasHeld = 0;
        		lastLand = -1;
			}
		}
		else
    		lastLand = -1;

		if (isGameEnd(&board)){
        	SDL_Quit();
    	}


		//Render New Frame
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		drawPiece(renderer, &piece);
		drawBoard(renderer, &board);
		drawGhostPiece(renderer, &board, &piece);
		drawHold(renderer, &hold, font);
		drawNext(renderer, font, pieceBucketCurrent, pieceBucketNext, bucketIndex);
		drawScore(renderer, font, score);
	
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	//Close
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
