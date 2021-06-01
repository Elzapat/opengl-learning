#include <stdio.h>
#include <math.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include <glad/glad.h>

#include "../include/shader.h"
#include "../include/shapes.h"
#include "../include/textures.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

// Settings
static unsigned int screen_width = 800;
static unsigned int screen_height = 600;
static float mix_value = 0.5f;
static vec3 camera_translate = { 0.0f, 0.0f, -3.0f };

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

    glEnable(GL_DEPTH_TEST);

    /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

    while (!glfwWindowShouldClose(window)) {
        // input
        process_input(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        // --------------------------------------------
        // 3D Julien
        glUseProgram(threeD_shader_program);
        glBindVertexArray(julien_cube);

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

        mat4 view = GLM_MAT4_IDENTITY_INIT;
        /* glm_translate(view, (vec3){ 0.0f, 0.0f, -3.0f }); */
        glm_translate(view, camera_translate);
        mat4 projection;
        glm_perspective(glm_rad(45.0f), screen_width / screen_height, 0.1f, 100.0f, projection);

        int model_loc = glGetUniformLocation(threeD_shader_program, "model");
        int view_loc = glGetUniformLocation(threeD_shader_program, "view");
        int projection_loc = glGetUniformLocation(threeD_shader_program, "projection");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float*)view);
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float*)projection);

        for (int i = 0; i < 10; i++) {
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate(model, cube_positions[i]);
            glm_rotate(model, glfwGetTime() * (i + 1), (vec3){ 0.5f, 1.0f, 0.0f });
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera_translate[2] += 0.1f;
        mix_value += 0.02f;
        if (mix_value >= 10.0f)
            mix_value = 10.0f;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera_translate[2] -= 0.1f;
        mix_value -= 0.02f;
        if (mix_value <= -10.0f)
            mix_value = -10.0f;
    }
}
