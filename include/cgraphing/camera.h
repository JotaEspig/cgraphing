#ifndef CAMERA_H
#define CAMERA_H

#include <cgraphing/vec3.h>
#include <cgraphing/mat4.h>

typedef struct cg_camera_t
{
    cg_vec3_t pos;
    cg_vec3_t front;
    cg_vec3_t up;
} cg_camera_t;

cg_camera_t cg_new_camera();
cg_mat4_t cg_camera_get_view(cg_camera_t cam);
cg_mat4_t cg_camera_look_at(cg_vec3_t eye, cg_vec3_t center, cg_vec3_t up);

#endif // CAMERA_H
