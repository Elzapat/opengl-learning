#include <stdio.h>
#include <math.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include <glad/glad.h>

#include "../include/shader.h"
#include "../include/shapes.h"
#include "../include/textures.h"
#include "../include/camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

// Settings
static unsigned int screen_width = 800;
static unsigned int screen_height = 600;
static float mix_value = 0.5f;
static GLboolean enable_2D = GL_TRUE;

// Camera
static Camera camera;
static float last_mouse_x = 800.f / 2.f;
static float last_mouse_y = 600.f / 2.f;
static GLboolean first_mouse = GL_TRUE;

// Timing
float delta_time = 0.0f;
float last_frame = 0.0f;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "learn-opengl", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to intialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    vec3 cube_positions[] = {
        {  0.0f,  0.0f,   0.0f },
        {  2.0f,  5.0f, -15.0f },
        { -1.5f, -2.2f,  -2.5f },
        { -3.8f, -2.0f, -12.3f },
        {  2.4f, -0.4f,  -3.5f },
        { -1.7f,  3.0f,  -7.5f },
        {  1.3f, -2.0f,  -2.5f },
        {  1.5f,  2.0f,  -2.5f },
        {  1.5f,  0.2f,  -1.5f },
        { -1.3f,  1.0f,  -1.5f }
    };

    unsigned int shader_program = create_shader_program(
            "src/shaders/vertex_shader.vert", "src/shaders/frag_shader.frag");
    unsigned int yellow_shader_program = create_shader_program(
            "src/shaders/vertex_shader.vert", "src/shaders/yellow_frag_shader.frag");
    unsigned int texture_shader_program = create_shader_program(
            "src/shaders/tex_vertex_shader.vert", "src/shaders/tex_frag_shader.vert");
    unsigned int trans_shader_program = create_shader_program(
            "src/shaders/trans_vertex_shader.vert", "src/shaders/trans_fragment_shader.frag");
    unsigned int threeD_shader_program = create_shader_program(
            "src/shaders/3d_vertex_shader.vert", "src/shaders/3d_fragment_shader.frag");

    unsigned int first_triangle = create_first_triangle();
    unsigned int second_triangle = create_second_triangle();
    unsigned int rectangle = create_rectangle();
    unsigned int rainbow_rectangle = create_rainbow_rect();
    unsigned int julien_cube = create_cube();

    unsigned int benoit_texture = create_benoit_texture();
    unsigned int aragorgne_texture = create_aragorgne_texture();
    unsigned int julien_texture = create_julien_texture();

    glUseProgram(texture_shader_program);
    glUniform1i(glGetUniformLocation(texture_shader_program, "texture1"), 0);
    glUniform1i(glGetUniformLocation(texture_shader_program, "texture2"), 1);

    glUseProgram(threeD_shader_program);
    glUniform1i(glGetUniformLocation(threeD_shader_program, "texture1"), 2);

    camera = camera_new(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        // delta time calculation
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // input
        process_input(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (enable_2D) {
            // --------------------------------------------
            // Moving triangle
            glUseProgram(shader_program);
            glBindVertexArray(first_triangle);

            float time_value = glfwGetTime();
            float horizontal_offset = sin(time_value) / 2.0f;
            float vertical_offset = cos(time_value) / 2.0f;

            int horizontal_offset_location = glGetUniformLocation(
                    shader_program, "horizontal_offset");
            if (horizontal_offset_location == -1) {
                printf("Error retrieving the horizontal offset location\n");
                return -1;
            }
            int vertical_offset_location = glGetUniformLocation(
                    shader_program, "vertical_offset");
            if (horizontal_offset_location == -1) {
                printf("Error retrieving the vertical offset location\n");
                return -1;
            }

            glUniform1f(horizontal_offset_location, horizontal_offset);
            glUniform1f(vertical_offset_location, vertical_offset);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            // --------------------------------------------
            // Static triangle
            glUseProgram(yellow_shader_program);
            glBindVertexArray(second_triangle);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // --------------------------------------------
            // Textured rectangle
            glUseProgram(texture_shader_program);
            glUniform1f(glGetUniformLocation(texture_shader_program, "mix_value"), mix_value);
            glBindVertexArray(rectangle);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            // --------------------------------------------
            // Transformed rainbow rectangle
            glUseProgram(trans_shader_program);
            glBindVertexArray(rainbow_rectangle);

            mat4 trans = GLM_MAT4_IDENTITY_INIT;
            glm_translate(trans, (vec3){ 0.2f, -0.2f, 0.0f });
            glm_rotate(trans, glm_rad(50 * time_value), (vec3){ 0.0, 0.0, 1.0 });
            glm_scale(trans, (vec3){ 0.5f, 0.7f, 0.5f });

            unsigned int transform_location = glGetUniformLocation(trans_shader_program, "transform");
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, (float *)trans);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            mat4 trans2 = GLM_MAT4_IDENTITY_INIT;
            glm_translate(trans2, (vec3){ -0.5f, 0.5f, 0.0f });
            glm_scale(trans2, (vec3){ sin(time_value), 0.2f, 0.5f });

            glUniformMatrix4fv(transform_location, 1, GL_FALSE, (float*)trans2);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        // --------------------------------------------
        // 3D Julien
        glUseProgram(threeD_shader_program);
        glBindVertexArray(julien_cube);

        mat4 projection;
        glm_perspective(glm_rad(camera.zoom), (float)screen_width / (float)screen_height, 0.1f, 100.0f, projection);
        int projection_loc = glGetUniformLocation(threeD_shader_program, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float*)projection);

        mat4 view;
        camera_view_matrix(&camera, view);
        int view_loc = glGetUniformLocation(threeD_shader_program, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float*)view);

        for (int i = 0; i < 10; i++) {
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate(model, cube_positions[i]);
            glm_rotate(model, glfwGetTime() * (i + 1), (vec3){ 0.5f, 1.0f, 0.0f });
            int model_loc = glGetUniformLocation(threeD_shader_program, "model");
            glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // events and swapping buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &first_triangle);
    glDeleteVertexArrays(1, &second_triangle);
    glDeleteBuffers(1, &rectangle);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    screen_width = width;
    screen_height = height;
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mix_value += 0.02f;
        if (mix_value >= 10.0f)
            mix_value = 10.0f;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mix_value -= 0.02f;
        if (mix_value <= -10.0f)
            mix_value = -10.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        enable_2D = !enable_2D;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_process_keyboard(&camera, FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_process_keyboard(&camera, BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_process_keyboard(&camera, LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_process_keyboard(&camera, RIGHT, delta_time);
}

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos) {
    if (first_mouse) {
        last_mouse_x = x_pos;
        last_mouse_y = y_pos;
        first_mouse = GL_FALSE;
    }

    float x_offset = (float)x_pos - last_mouse_x;
    float y_offset = last_mouse_y - (float)y_pos;

    last_mouse_x = (float)x_pos;
    last_mouse_y = (float)y_pos;

    camera_process_mouse_move(&camera, (float)x_offset, (float)y_offset, GL_TRUE);
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    camera_process_mouse_scroll(&camera, (float)y_offset);
}
