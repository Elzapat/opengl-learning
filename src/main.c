#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "../include/shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
unsigned int create_first_triangle();
unsigned int create_second_triangle();

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* unsigned int indices[] = { */
    /*     0, 1, 3, */
    /*     1, 2, 3 */
    /* }; */

    /* unsigned int orange_shader_program = create_shader_program( */
    /*         "src/vertex_shader.vert", "src/orange_frag_shader.frag"); */
    /* unsigned int yellow_shader_program = create_shader_program( */
    /*         "src/vertex_shader.vert", "src/yellow_frag_shader.frag"); */

    unsigned int shader_program = create_shader_program(
            "src/vertex_shader.vert", "src/frag_shader.frag");

    unsigned int first_triangle = create_first_triangle();
    unsigned int second_triangle = create_second_triangle();

    /* unsigned int EBO; */
    /* glGenBuffers(1, &EBO); */
    /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); */
    /* glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); */

    /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

    while (!glfwWindowShouldClose(window)) {
        // input
        process_input(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);

        float time_value = glfwGetTime();
        float green_value = (sin(time_value) / 2.0f) + 0.5f;
        int vertex_color_location = glGetUniformLocation(shader_program, "ourColor");
        if (vertex_color_location == -1) {
            printf("Error retrieving the vertex color location\n");
            return -1;
        }

        glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);

        glBindVertexArray(first_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* glUseProgram(yellow_shader_program); */

        glBindVertexArray(second_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); */
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

        // events and swapping buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

unsigned int create_first_triangle() {
    float vertices[] = {
        -0.5f, 0.5f, 0.0f,
         0.5f, 0.5f, 0.0f,
         0.0f, 0.0f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}

unsigned int create_second_triangle() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.0f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}
