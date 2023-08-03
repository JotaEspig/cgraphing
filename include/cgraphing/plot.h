#ifndef PLOT_H
#define PLOT_H

#include <SDL2/SDL.h>

#include <cgraphing/pair.h>

typedef struct cg_plot_t
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    cg_pair_list_t *pairs;
} cg_plot_t;

cg_plot_t *cg_new_plot(const char *title, int width, int height);
void cg_plot_add_pair(cg_plot_t *plot, cg_pair_t pair);
void cg_plot_show(cg_plot_t *plot);
void cg_plot_destroy(cg_plot_t *plot);

#endif // PLOT_H
