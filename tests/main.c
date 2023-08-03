#include <math.h>

#include <cgraphing/plot.h>
#include <cgraphing/pair.h>

int main()
{
    cg_plot_t *plot = cg_new_plot("Jota Cria", 800, 800);
    for (float i = -90; i <= 105; i += 0.1)
    {
        float y = fabs(powf(i, 2) + 6 * i - 40); // |x² +6x + 9|
        cg_pair_t pair = {i, y};
        cg_plot_add_pair(plot, pair);
    }
    cg_plot_show(plot);
    cg_plot_destroy(plot);
    return 0;
}