#include "SDL_events.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>

#include <cgraphing/plot.h>
#include <cgraphing/pair.h>
#include <cgraphing/mat4.h>
#include <cgraphing/vec3.h>
#include <cgraphing/camera.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

static void draw_grid(cg_plot_t *plot, cg_mat4_t mat_transform)
{
    int width, height;
    SDL_GetWindowSize(plot->window, &width, &height);

    for (float x = 0; x < width + 1; ++x)
    {
        cg_vec3_t v1 = cg_new_vec3(x, 0, 0);
        cg_vec3_t v2 = cg_new_vec3(x, height, 0);
        v1 = cg_mat4_mult_vec3(mat_transform, v1);
        v2 = cg_mat4_mult_vec3(mat_transform, v2);
        if (x > 0 && x < 10) {cg_vec3_print(v1);}
        SDL_RenderDrawLineF(plot->renderer, v1.x, v1.y, v2.x, v2.y);
        if (x == width / 2)
        {
            cg_vec3_t v1 = cg_new_vec3(x + 1, 0, 0);
            cg_vec3_t v2 = cg_new_vec3(x + 1, height, 0);
            v1 = cg_mat4_mult_vec3(mat_transform, v1);
            v2 = cg_mat4_mult_vec3(mat_transform, v2);
            SDL_RenderDrawLineF(plot->renderer, v1.x, v1.y, v2.x, v2.y);
        }
    }
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
        SDL_DestroyWindow(plot->window);
        free(plot);
        fprintf(stderr, "error initializing SDL_Renderer: %s\n", SDL_GetError());
        return NULL;
    }

    cg_pair_list_t *pairs = cg_new_pair_list();

    plot->window = window;
    plot->renderer = renderer;
    plot->pairs = pairs;
    plot->line_thickness = 1;
    plot->line_color = (SDL_Color){0, 0, 0, 255};
    plot->cam = cg_new_camera();
    return plot;
}

void cg_plot_add_pair(cg_plot_t *plot, cg_pair_t pair)
{
    cg_pair_list_append(plot->pairs, pair);
}

void cg_plot_show(cg_plot_t *plot)
{
    int width, height;
    SDL_GetWindowSize(plot->window, &width, &height);

    cg_pair_list_t *pairs = cg_new_pair_list();
    for (size_t i = 0; i < plot->pairs->size; ++i)
    {
        cg_pair_t new_p = plot->pairs->values[i];
        cg_pair_list_append(pairs, to_sdl_coordinates(plot, new_p));
    }

    cg_mat4_t perspective = cg_camera_perspective(M_PI / 4, width / height, 0.1, 100);
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

            case SDL_KEYDOWN:
                plot->cam.pos = cg_vec3_add(plot->cam.pos, plot->cam.front);
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(plot->renderer, 255, 255, 255, 255);
        SDL_RenderClear(plot->renderer);

        cg_mat4_t view = cg_camera_get_view(plot->cam);
        cg_mat4_t mat = cg_mat4_mult(perspective, view);

        SDL_SetRenderDrawColor(plot->renderer, 0, 0, 0, 255);
        cg_mat4_print(mat);
        draw_grid(plot, mat);

        SDL_SetRenderDrawColor(plot->renderer,
                               plot->line_color.r, plot->line_color.g, plot->line_color.b,
                               plot->line_color.a);
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

                cg_vec3_t v1 = {p.x, p.y, 0};
                cg_vec3_t v2 = {next_p.x, next_p.y, 0};
                /*
                v1 = cg_mat4_mult_vec3(mat, v1);
                v2 = cg_mat4_mult_vec3(mat, v2);
                */

                for (int j = 0; j < plot->line_thickness; ++j)
                    for (int k = 0; k < plot->line_thickness; ++k)
                        SDL_RenderDrawLineF(plot->renderer,
                                            v1.x + j, v1.y + k, v2.x + j, v2.y + k);
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
