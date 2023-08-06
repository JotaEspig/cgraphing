#ifndef VEC3_H
#define VEC3_H

typedef struct cg_vec3_t
{
    float x;
    float y;
    float z;
} cg_vec3_t;

cg_vec3_t cg_new_vec3(float x, float y, float z);
cg_vec3_t cg_vec3_add(cg_vec3_t a, cg_vec3_t b);
cg_vec3_t cg_vec3_sub(cg_vec3_t a, cg_vec3_t b);
float cg_vec3_dot(cg_vec3_t a, cg_vec3_t b);
cg_vec3_t cg_vec3_cross(cg_vec3_t a, cg_vec3_t b);
cg_vec3_t cg_vec3_scalar_div(cg_vec3_t vec, float val);
cg_vec3_t cg_vec3_normalize(cg_vec3_t vec);
float cg_vec3_length(cg_vec3_t vec);
void cg_vec3_print(cg_vec3_t vec);

#endif // VEC3_H
