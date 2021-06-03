#include "../include/camera.h"

Camera camera_new(float x, float y, float z, float up_x, float up_y, float up_z) {
    Camera new_camera = {
        .position = { x, y, z },
        .front = { 0.0f, 1.0f, 0.0f },
        .world_up = { up_x, up_y, up_z },
        .yaw = YAW,
        .pitch = PITCH,
        .movement_speed = SPEED,
        .mouse_sensitivity = SENSITIVITY,
        .zoom = ZOOM
    };
    camera_update_vectors(&new_camera);
    return new_camera;
};

void camera_view_matrix(Camera* camera, mat4 dest) {
    vec3 direction;
    glm_vec3_add(camera->position, camera->front, direction);
    glm_lookat(camera->position, direction, camera->up, dest);
    /*  */
    /* vec3 target; */
    /* glm_vec3_add(camera->position, camera->front, target); */
    /*  */
    /* vec3 z_axis; */
    /* glm_vec3_sub(camera->position, target, z_axis); */
    /* glm_normalize(z_axis); */
    /*  */
    /* vec3 x_axis; */
    /* glm_vec3_copy(camera->up, x_axis); */
    /* glm_normalize(x_axis); */
    /* glm_cross(x_axis, z_axis, x_axis); */
    /* glm_normalize(x_axis); */
    /*  */
    /* vec3 y_axis; */
    /* glm_cross(z_axis, x_axis, y_axis); */
    /*  */
    /* mat4 rotation = { */
    /*     { x_axis[0], y_axis[0], z_axis[0], 0.0f }, */
    /*     { x_axis[1], y_axis[1], z_axis[1], 0.0f }, */
    /*     { x_axis[2], y_axis[2], z_axis[2], 0.0f }, */
    /*     { 0.0f     , 0.0f     , 0.0f     , 1.0f } */
    /* }; */
    /*  */
    /* mat4 translation = { */
    /*     { 1.0f, 0.0f, 0.0f, 0.0f }, */
    /*     { 0.0f, 1.0f, 0.0f, 0.0f }, */
    /*     { 0.0f, 0.0f, 1.0f, 0.0f }, */
    /*     { -camera->position[0], -camera->position[1], -camera->position[2], 1.0f } */
    /* }; */
    /*  */
    /* glm_mul(rotation, translation, dest); */
}

void camera_process_keyboard(Camera* camera, CameraMovement direction, float dt) {
    float velocity = camera->movement_speed * dt;
    if (direction == FORWARD)
        glm_vec3_muladds(camera->front, velocity, camera->position);
    else if (direction == BACKWARD)
        glm_vec3_muladds(camera->front, -velocity, camera->position);
    else if (direction == LEFT)
        glm_vec3_muladds(camera->right, -velocity, camera->position);
    else if (direction == RIGHT)
        glm_vec3_muladds(camera->right, velocity, camera->position);
}

void camera_process_mouse_move(Camera* camera, float x_offset, float y_offset,
        GLboolean constrain_pitch) {
    x_offset *= camera->mouse_sensitivity;
    y_offset *= camera->mouse_sensitivity;

    camera->yaw += x_offset;
    camera->pitch += y_offset;

    if (constrain_pitch) {
        if (camera->pitch > 89.0f)
            camera->pitch = 89.0f;
        else if (camera->pitch < -89.0f)
            camera->pitch = -89.0f;
    }

    camera_update_vectors(camera);
}

void camera_process_mouse_scroll(Camera* camera, float y_offset) {
    camera->zoom -= y_offset;
    if (camera->zoom < 1.0f)
        camera->zoom = 1.0f;
    else if (camera->zoom > 90.0f)
        camera->zoom = 90.0f;
}

void camera_update_vectors(Camera* camera) {
    camera->front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    camera->front[1] = sin(glm_rad(camera->pitch));
    camera->front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_normalize(camera->front);

    glm_cross(camera->front, camera->world_up, camera->right);
    glm_normalize(camera->right);

    glm_cross(camera->right, camera->front, camera->up);
    glm_normalize(camera->up);
}
