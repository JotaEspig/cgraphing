#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <cgraphing/plot.h>
#include <cgraphing/pair.h>

static cg_pair_t to_sdl_coordinates(cg_plot_t *plot, cg_pair_t pair)
{
    cg_pair_t new_pair;
    int width, height;
    SDL_GetWindowSize(plot->window, &width, &height);
    // Y is a subtraction because SDL Y coordinates system is the opposite of a normal
    // cartesian plane
    new_pair.x = (width / 2) + pair.x;
    new_pair.y = (height / 2) - pair.y;
    return new_pair;
}

cg_plot_t *cg_new_plot(const char *title, int width, int height)
{
    cg_plot_t *plot;
    plot = (cg_plot_t *)malloc(sizeof(cg_plot_t));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        free(plot);
        fprintf(stderr, "error initializing SDL: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height, 0);
    if (window == NULL)
    {
        free(plot);
        fprintf(stderr, "error initializing SDL_Window: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        free(window);
        free(plot);
        fprintf(stderr, "error initializing SDL_Renderer: %s\n", SDL_GetError());
        return NULL;
    }

    cg_pair_list_t *pairs = cg_new_pair_list();

    plot->window = window;
    plot->renderer = renderer;
    plot->pairs = pairs;
    return plot;
}

void cg_plot_add_pair(cg_plot_t *plot, cg_pair_t pair, float initial_x, float final_x)
{
    int width, height;
    SDL_GetWindowSize(plot->window, &width, &height);

    float div = fabs(initial_x) + fabs(final_x);
    pair.x *= width / div + (initial_x + final_x);
    pair.y *= height / div;
    cg_pair_t sdl_pair = to_sdl_coordinates(plot, pair);
    cg_pair_list_append(plot->pairs, sdl_pair);
}

void cg_plot_show(cg_plot_t *plot)
{
    int exit = 0;
    while (!exit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit = 1;
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(plot->renderer, 255, 255, 255, 255);
        SDL_RenderClear(plot->renderer);

        SDL_SetRenderDrawColor(plot->renderer, 0, 0, 0, 255);
        if (plot->pairs->size == 1)
        {
            SDL_RenderDrawPointF(plot->renderer,
                                 plot->pairs->values[0].x,
                                 plot->pairs->values[0].y);
        }
        else
        {
            for (size_t i = 0; i < plot->pairs->size - 1; ++i)
            {
                cg_pair_t p = plot->pairs->values[i];
                cg_pair_t next_p = plot->pairs->values[i + 1];
                SDL_RenderDrawLineF(plot->renderer,
                                    p.x, p.y, next_p.x, next_p.y);
            }
        }

        SDL_RenderPresent(plot->renderer);
    }
}

void cg_plot_destroy(cg_plot_t *plot)
{
    free(plot->window);
    free(plot->renderer);
    cg_pair_list_destroy(plot->pairs);
    free(plot);
}
