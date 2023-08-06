#include <stdio.h>

#include <cgraphing/mat4.h>
#include <cgraphing/vec3.h>

typedef struct vec4_t
{
    cg_vec3_t vec3;
    float w;
} vec4_t;

cg_mat4_t cg_new_mat4(float type)
{
    cg_mat4_t mat4;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            mat4.values[i][j] = (type == 1 && i == j) ? 1 : 0;

    return mat4;
}

cg_mat4_t cg_mat4_mult(cg_mat4_t m1, cg_mat4_t m2)
{
    cg_mat4_t mat = cg_new_mat4(0);

    float a[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            a[i][j] = m1.values[i][j];

    float b[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            b[i][j] = m2.values[i][j];

    // TODO Finish this mf
    mat.values[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0];
    mat.values[0][1] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    mat.values[0][2];
    mat.values[0][3];
    mat.values[1][0];
    mat.values[1][1];
    mat.values[1][2];
    mat.values[1][3];
    mat.values[2][0];
    mat.values[2][1];
    mat.values[2][2];
    mat.values[2][3];
    mat.values[3][0];
    mat.values[3][1];
    mat.values[3][2];
    mat.values[3][3];
    return mat;
}

cg_vec3_t cg_mat4_mult_vec3(cg_mat4_t mat, cg_vec3_t vec)
{
    vec4_t vec4 = {vec, 1};
    vec4_t new_vec4 = {{0, 0, 0}, 0};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            *((float *)&new_vec4 + i) += mat.values[i][j] * *((float *)&vec4 + j); // :)

    return new_vec4.vec3;
}

void cg_mat4_print(cg_mat4_t mat)
{
    printf("Mat4: ");
    for (int i = 0; i < 4; ++i)
    {
        printf("\t");
        for (int j = 0; j < 3; ++j)
            printf("%f - ", mat.values[i][j]);
        printf("%f\n", mat.values[i][3]);
    }
}
