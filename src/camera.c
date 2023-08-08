#include <cgraphing/camera.h>
#include <cgraphing/vec3.h>
#include <cgraphing/mat4.h>
#include <math.h>

cg_camera_t cg_new_camera()
{
    cg_camera_t cam;
    cam.pos = (cg_vec3_t){0.0, 0.0, 0.0};
    cam.front = (cg_vec3_t){0.0, 0.0, -1.0};
    cam.up = (cg_vec3_t){0.0, 1.0, 0.0};
    return cam;
}

cg_mat4_t cg_camera_get_view(cg_camera_t cam)
{
    return cg_camera_look_at(cam.pos, cg_vec3_add(cam.pos, cam.front), cam.up);
}

cg_mat4_t cg_camera_look_at(cg_vec3_t eye, cg_vec3_t center, cg_vec3_t up)
{
    cg_mat4_t matrix;
    cg_vec3_t x_axis, y_axis, z_axis;
    z_axis = cg_vec3_sub(eye, center);
    z_axis = cg_vec3_normalize(z_axis);
    y_axis = up;
    x_axis = cg_vec3_cross(y_axis, z_axis);
    y_axis = cg_vec3_cross(z_axis, x_axis);
    x_axis = cg_vec3_normalize(x_axis);
    y_axis = cg_vec3_normalize(y_axis);

    matrix.values[0][0] = x_axis.x;
    matrix.values[1][0] = x_axis.y;
    matrix.values[2][0] = x_axis.z;
    matrix.values[3][0] = -cg_vec3_dot(x_axis, eye);
    matrix.values[0][1] = y_axis.x;
    matrix.values[1][1] = y_axis.y;
    matrix.values[2][1] = y_axis.z;
    matrix.values[3][1] = -cg_vec3_dot(y_axis, eye);
    matrix.values[0][2] = z_axis.x;
    matrix.values[1][2] = z_axis.y;
    matrix.values[2][2] = z_axis.z;
    matrix.values[3][2] = -cg_vec3_dot(z_axis, eye);
    matrix.values[0][3] = 0;
    matrix.values[1][3] = 0;
    matrix.values[2][3] = 0;
    matrix.values[3][3] = 1;

    return matrix;
}

cg_mat4_t cg_camera_perspective(float fov, float aspect_radio, float near, float far)
{
    cg_mat4_t mat = cg_new_mat4(1);
    float x = 1 / tanf(fov / 2);

    mat.values[0][0] = aspect_radio * x;
    mat.values[1][1] = x;
    mat.values[2][2] = far / (far - near);
    mat.values[2][3] = -1;
    mat.values[3][2] = (-far * near) / (far - near);
    mat.values[3][3] = 0;

    return mat;
}
