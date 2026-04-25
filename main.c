#include <stdio.h>
#include <SDL2/SDL.h>

//https://tetris.wiki/Tetris_Guideline
//TODO: Kyle read the guidelines for the project!

int main(){

    //Block initilizes the SDL engine. SDL Init says we want ot use video, then we create a centered tetris window, and render it.
    SDL_Init(SDL_INIT_VIDEO); //SDL_Init(SDL_INIT_AUDIO); Include only if we want to code in sound
    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //The -1 just tells the program to use the best renderer for the situation!


}
