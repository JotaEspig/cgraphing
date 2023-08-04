#include <math.h>

#include <cgraphing/plot.h>
#include <cgraphing/pair.h>

int main()
{
    cg_plot_t *plot = cg_new_plot("Plot", 600, 600);
    for (float x = -90; x <= 105; x += 0.1)
    {
        float y = x * x + 6 * x + 9; // x² +6x + 9
        cg_pair_t pair = {x, y};
        cg_plot_add_pair(plot, pair);
    }
    plot->line_thickness = 2;
    cg_plot_show(plot, -30, 30);
    cg_plot_destroy(plot);
    return 0;
}