#ifndef MAT4_H
#define MAT4_H

#include <cgraphing/vec3.h>

typedef struct cg_mat4_t
{
    float values[4][4];
} cg_mat4_t;

cg_mat4_t cg_new_mat4(float type);
cg_mat4_t cg_mat4_mult(cg_mat4_t m1, cg_mat4_t m2);
cg_vec3_t cg_mat4_mult_vec3(cg_mat4_t mat, cg_vec3_t vec);
void cg_mat4_print(cg_mat4_t mat);

#endif // MAT4_F
