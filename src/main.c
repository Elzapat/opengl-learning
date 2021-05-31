#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
unsigned int create_first_triangle();
unsigned int create_second_triangle();
unsigned int create_rectangle();
unsigned int create_benoit_texture();

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

    unsigned int shader_program = create_shader_program(
            "src/vertex_shader.vert", "src/frag_shader.frag");
    unsigned int yellow_shader_program = create_shader_program(
            "src/vertex_shader.vert", "src/yellow_frag_shader.frag");
    unsigned int texture_shader_program = create_shader_program(
            "src/tex_vertex_shader.vert", "src/tex_frag_shader.vert");

    unsigned int first_triangle = create_first_triangle();
    unsigned int second_triangle = create_second_triangle();
    unsigned int rectangle = create_rectangle();

    unsigned int benoit_texture = create_benoit_texture();

    /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

    while (!glfwWindowShouldClose(window)) {
        // input
        process_input(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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

        glUseProgram(yellow_shader_program);

        glBindVertexArray(second_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        /* unsigned int texture_location = glGetUniformLocation( */
        /*         texture_shader_program, "ourTexture"); */
        /* if (texture_location == -1) { */
        /*     printf("Error retrieving texture location"); */
        /*     return -1; */
        /* } */
        /* glBindTexture(GL_TEXTURE_2D, benoit_texture); */
        glUseProgram(texture_shader_program);
        glBindVertexArray(rectangle);
        /* glDrawArrays(GL_TRIANGLES, 0, 3); */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle); */
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

        /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); */
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

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
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

unsigned int create_first_triangle() {
    float vertices[] = {
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

unsigned int create_rectangle() {
    float vertices[] = {
        // position         // colors         // texture coords
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right 
        -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -1.0f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
            (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    return VAO;
}

unsigned int create_benoit_texture() {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nb_channels;
    unsigned char* image_data = stbi_load("assets/benoit.jpg", &width, &height,
            &nb_channels, 0);

    if (!image_data) {
        printf("Error loading texture\n");
        exit(-1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image_data);

    return texture;
}
