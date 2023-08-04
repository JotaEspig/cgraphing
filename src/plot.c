#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <cgraphing/plot.h>
#include <cgraphing/pair.h>
#include <cgraphing/color.h>

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
    plot->line_thickness = 1;
    plot->line_color.r = 0;
    plot->line_color.g = 0;
    plot->line_color.b = 0;
    plot->line_color.alpha = 255;
    return plot;
}

void cg_plot_add_pair(cg_plot_t *plot, cg_pair_t pair)
{
    cg_pair_list_append(plot->pairs, pair);
}

void cg_plot_show(cg_plot_t *plot, float initial_x, float final_x)
{
    int width, height;
    SDL_GetWindowSize(plot->window, &width, &height);

    float div = fabs(initial_x) + fabs(final_x);
    float scale_x = width / div;
    float scale_y = height / div;
    float offset_x = (initial_x + final_x) / 2;
    cg_pair_list_t *pairs = cg_new_pair_list();

    for (size_t i = 0; i < plot->pairs->size; ++i)
    {
        cg_pair_t new_p = plot->pairs->values[i];
        new_p.x *= scale_x;
        new_p.x += offset_x;
        new_p.y *= scale_y;
        cg_pair_list_append(pairs, to_sdl_coordinates(plot, new_p));
    }

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

        SDL_SetRenderDrawColor(plot->renderer,
                               plot->line_color.r, plot->line_color.g, plot->line_color.b,
                               plot->line_color.alpha);
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
                cg_pair_t p = pairs->values[i];
                cg_pair_t next_p = pairs->values[i + 1];

                float x1 = p.x;
                float y1 = p.y;
                float x2 = next_p.x;
                float y2 = next_p.y;

                for (int j = 0; j < plot->line_thickness; ++j)
                    for (int k = 0; k < plot->line_thickness; ++k)
                        SDL_RenderDrawLineF(plot->renderer,
                                            x1 + j, y1 + k, x2 + j, y2 + k);
            }
        }

        SDL_RenderPresent(plot->renderer);
    }

    cg_pair_list_destroy(pairs);
}

void cg_plot_destroy(cg_plot_t *plot)
{
    SDL_DestroyWindow(plot->window);
    SDL_DestroyRenderer(plot->renderer);
    cg_pair_list_destroy(plot->pairs);
    free(plot);
}
