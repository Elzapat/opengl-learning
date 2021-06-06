#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <cglm/cglm.h>

#define YAW          -90.0f
#define PITCH        0.0f
#define SPEED        3.0f
#define SENSITIVITY  0.1f
#define ZOOM         45.0f

struct Camera {
    // camera attributes
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 world_up;
    // euler angles
    float yaw;
    float pitch;
    // camera options
    float movement_speed;
    float mouse_sensitivity;
    float zoom;
    // screen properties
    unsigned int screen_width;
    unsigned int screen_height;
};

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

typedef struct Camera Camera;
typedef enum CameraMovement CameraMovement;

Camera camera_new(float x, float y, float z, float up_x, float up_y, float up_z);
void camera_view_matrix(Camera* camera, mat4 dest);
void camera_process_keyboard(Camera* camera, CameraMovement direction, float dt);
void camera_process_mouse_move(Camera* camera, float x_offset, float y_offset,
        GLboolean constrain_pitch);
void camera_process_mouse_scroll(Camera* camera, float y_offset);
void camera_update_vectors(Camera* camera);

#endif // CAMERA_H
