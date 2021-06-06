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
static float mix_value = 0.5f;
static GLboolean enable_2D = GL_FALSE;

// Camera
static Camera camera;
static float last_mouse_x = 800.f / 2.f;
static float last_mouse_y = 600.f / 2.f;
static GLboolean first_mouse = GL_TRUE;

// Timing
static float delta_time = 0.0f;
static float last_frame = 0.0f;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "learn-opengl", NULL, NULL);
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

    camera = camera_new(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f);

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
    unsigned int lighting_shader = create_shader_program(
            "src/shaders/basic_vertex_shader.vert", "src/shaders/light_fragment_shader.frag");
    unsigned int basic_shader = create_shader_program(
            "src/shaders/basic_vertex_shader.vert", "src/shaders/basic_fragment_shader.frag");

    unsigned int first_triangle = create_first_triangle();
    unsigned int second_triangle = create_second_triangle();
    unsigned int rectangle = create_rectangle();
    unsigned int rainbow_rectangle = create_rainbow_rect();
    unsigned int julien_cube = create_cube();
    unsigned int light_source = create_cube();
    unsigned int reflecting_cube = create_cube();

    unsigned int benoit_texture = create_benoit_texture();
    unsigned int aragorgne_texture = create_aragorgne_texture();
    unsigned int julien_texture = create_julien_texture();

    // Set the textures of the shader program (aragorgne and benoit)
    glUseProgram(texture_shader_program);
    glUniform1i(glGetUniformLocation(texture_shader_program, "texture1"), 0);
    glUniform1i(glGetUniformLocation(texture_shader_program, "texture2"), 1);

    // Set the texture (julien)
    glUseProgram(threeD_shader_program);
    glUniform1i(glGetUniformLocation(threeD_shader_program, "texture1"), 2);

    // Set the color of the light and the object
    const vec3 light_color = { 1.0f, 1.0f, 1.0f };

    glUseProgram(lighting_shader);
    glUniform3fv(glGetUniformLocation(lighting_shader, "lightColor"), 1, light_color);

    glUseProgram(basic_shader);
    glUniform3fv(glGetUniformLocation(basic_shader, "lightColor"), 1, light_color);
    glUniform3fv(glGetUniformLocation(basic_shader, "objectColor"), 1, (vec3){ 1.0f, 0.5f, 0.1f });

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

        float time_value = glfwGetTime();

        if (enable_2D) {
            draw_moving_triangle(shader_program, first_triangle, time_value);
            draw_static_triangle(yellow_shader_program, second_triangle);
            draw_textured_rectangle(texture_shader_program, rectangle, mix_value);
            draw_transformed_rectangle(trans_shader_program, rainbow_rectangle, time_value);
        }
        draw_julien(threeD_shader_program, julien_cube, &camera, time_value);
        draw_light_source(lighting_shader, light_source, &camera);
        draw_simple_cube(basic_shader, reflecting_cube, &camera, (vec3){ 4.0f, 3.0f, 1.0f });

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
    camera.screen_width = width;
    camera.screen_height = height;
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
