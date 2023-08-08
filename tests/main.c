#include <math.h>

#include <cgraphing/plot.h>
#include <cgraphing/pair.h>
#include <cgraphing/vec3.h>
#include <cgraphing/mat4.h>

int main()
{
    /*
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

    cg_mat4_t m1 = cg_new_mat4(1);
    m1.values[0][1] = 2;
    m1.values[2][3] = 1.5;
    cg_mat4_t m2 = cg_new_mat4(1);
    m2.values[0][1] = 1;
    m2.values[0][2] = 11;
    m2.values[0][3] = 1;
    m2.values[2][3] = 4;
    cg_mat4_t m3 = cg_mat4_mult(m1, m2);
    cg_mat4_print(m3);

    vec = cg_new_vec3(9, 0, 0);
    mat = cg_new_mat4(0);
    mat.values[0][0] = 2.414;
    mat.values[1][1] = 2.414;
    mat.values[2][2] = -5.40;
    mat.values[2][3] = -0.2;
    mat.values[3][2] = -1;
    cg_vec3_print(vec);
    cg_mat4_print(mat);
    vec = cg_mat4_mult_vec3(mat, vec);
    cg_vec3_print(vec);
    */

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
    return 0;
}
