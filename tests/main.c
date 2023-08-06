#include <math.h>

#include <cgraphing/plot.h>
#include <cgraphing/pair.h>
#include <cgraphing/vec3.h>
#include <cgraphing/mat4.h>

int main()
{
    printf("Testing vec3 and mat4 operations:\n");
    cg_vec3_t vec = cg_new_vec3(1, 2, 3);
    cg_vec3_print(vec);
    cg_vec3_t vec1 = cg_vec3_normalize(vec);
    cg_vec3_print(vec1);
    cg_vec3_t vec2 = cg_new_vec3(1, 2, 2);
    cg_vec3_t vec3 = cg_vec3_cross(vec, vec2);
    cg_vec3_print(vec3);

    printf("\n");

    cg_mat4_t mat = cg_new_mat4(1);
    mat.values[1][1] = 2;
    mat.values[1][2] = -3;
    cg_mat4_print(mat);
    cg_vec3_t vec4 = cg_mat4_mult_vec3(mat, vec);
    cg_vec3_print(vec4);

    /*
    cg_plot_t *plot = cg_new_plot("Plot", 600, 600);
    for (float x = -90; x <= 105; x += 0.1)
    {
        float y = (x + 3) * (x - 3); // x² +6x + 9
        cg_pair_t pair = {x, y};
        cg_plot_add_pair(plot, pair);
    }
    plot->line_color.r = 255;
    plot->line_thickness = 3;
    cg_plot_show(plot);
    cg_plot_destroy(plot);
    */
    return 0;
}