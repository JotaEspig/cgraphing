#include <stdio.h>

#include <SDL2/SDL.h>

#include <cgraphing/window.h>

void print()
{
    printf("Hello World\n");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *window = SDL_CreateWindow("jota brabo",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 800, 0);

    while (1);
}