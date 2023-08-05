#include <math.h>

#include <cgraphing/plot.h>
#include <cgraphing/pair.h>
#include <cgraphing/color.h>

int main()
{
    cg_plot_t *plot = cg_new_plot("Plot", 600, 600);
    for (float x = -90; x <= 105; x += 0.1)
    {
        float y = (x + 3) * (x - 3); // x² +6x + 9
        cg_pair_t pair = {x, y};
        cg_plot_add_pair(plot, pair);
    }
    cg_color_t color = {255, 0, 0, 255};
    plot->line_color = color;
    plot->line_thickness = 3;
    cg_plot_show(plot);
    cg_plot_destroy(plot);
    return 0;
}