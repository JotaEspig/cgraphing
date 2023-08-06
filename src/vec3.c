#include <stdio.h>
#include <math.h>

#include <cgraphing/vec3.h>

cg_vec3_t cg_new_vec3(float x, float y, float z)
{
    return (cg_vec3_t){x, y, z};
}

cg_vec3_t cg_vec3_add(cg_vec3_t a, cg_vec3_t b)
{
    return (cg_vec3_t){a.x + b.x, a.y + b.y, a.z + b.z};
}

cg_vec3_t cg_vec3_sub(cg_vec3_t a, cg_vec3_t b)
{
    return (cg_vec3_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

float cg_vec3_dot(cg_vec3_t a, cg_vec3_t b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

cg_vec3_t cg_vec3_cross(cg_vec3_t a, cg_vec3_t b)
{
    return (cg_vec3_t){a.y * b.z - a.z * b.y,
                       a.z * b.x - a.x * b.z,
                       a.x * b.y - a.y * b.x};
}

cg_vec3_t cg_vec3_scalar_div(cg_vec3_t vec, float val)
{
    return (cg_vec3_t){vec.x / val, vec.y / val, vec.z / val};
}

cg_vec3_t cg_vec3_normalize(cg_vec3_t vec)
{
    return cg_vec3_scalar_div(vec, cg_vec3_length(vec));
}

float cg_vec3_length(cg_vec3_t vec)
{
    return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
}

void cg_vec3_print(cg_vec3_t vec)
{
    printf("Vec: ");
    for (int i = 0; i < 2; ++i)
        printf("%f - ", *((float *)&vec + i));

    printf("%f\n", vec.z);
}
