#include "../include/shapes.h"

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
        -0.0f, -0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right 
        -0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -1.0f, -0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
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

unsigned int create_rainbow_rect() {
    float vertices[] = {
        // position         // colors        
         1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top right 
         1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
         0.3f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
         0.3f, -0.0f, 0.0f, 1.0f, 1.0f, 0.0f  // top left
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}

unsigned int create_cube() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}

int draw_moving_triangle(unsigned int shader, unsigned int VAO, float time) {
    glUseProgram(shader);

    glBindVertexArray(VAO);

    float horizontal_offset = sin(time) / 2.0f;
    float vertical_offset = cos(time) / 2.0f;

    int horizontal_offset_location = glGetUniformLocation(
            shader, "horizontal_offset");
    if (horizontal_offset_location == -1) {
        printf("Error retrieving the horizontal offset location\n");
        return -1;
    }
    int vertical_offset_location = glGetUniformLocation(
            shader, "vertical_offset");
    if (horizontal_offset_location == -1) {
        printf("Error retrieving the vertical offset location\n");
        return -1;
    }

    glUniform1f(horizontal_offset_location, horizontal_offset);
    glUniform1f(vertical_offset_location, vertical_offset);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    return 0;
}

int draw_static_triangle(unsigned int shader, unsigned int VAO) {
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    return 0;
}

int draw_textured_rectangle(unsigned int shader, unsigned int VAO, float mix_value) {
    glUseProgram(shader);
    glUniform1f(glGetUniformLocation(shader, "mix_value"), mix_value);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 0;
}

int draw_transformed_rectangle(unsigned int shader, unsigned int VAO, float time) {
    glUseProgram(shader);
    glBindVertexArray(VAO);

    mat4 trans = GLM_MAT4_IDENTITY_INIT;
    glm_translate(trans, (vec3){ 0.2f, -0.2f, 0.0f });
    glm_rotate(trans, glm_rad(50 * time), (vec3){ 0.0, 0.0, 1.0 });
    glm_scale(trans, (vec3){ 0.5f, 0.7f, 0.5f });

    unsigned int transform_location = glGetUniformLocation(shader, "transform");
    glUniformMatrix4fv(transform_location, 1, GL_FALSE, (float *)trans);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    mat4 trans2 = GLM_MAT4_IDENTITY_INIT;
    glm_translate(trans2, (vec3){ -0.5f, 0.5f, 0.0f });
    glm_scale(trans2, (vec3){ sin(time), 0.2f, 0.5f });

    glUniformMatrix4fv(transform_location, 1, GL_FALSE, (float*)trans2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 0;
}

int draw_julien(unsigned int shader, unsigned int VAO, Camera* camera, float time) {
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

    glUseProgram(shader);
    glBindVertexArray(VAO);

    mat4 projection;
    glm_perspective(glm_rad(camera->zoom),
            (float)camera->screen_width / (float)camera->screen_height,
            0.1f, 100.0f, projection);
    int projection_loc = glGetUniformLocation(shader, "projection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float*)projection);

    mat4 view;
    camera_view_matrix(camera, view);
    int view_loc = glGetUniformLocation(shader, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float*)view);

    for (int i = 0; i < 10; i++) {
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        glm_translate(model, cube_positions[i]);
        glm_rotate(model, time * (i + 1), (vec3){ 0.5f, 1.0f, 0.0f });
        int model_loc = glGetUniformLocation(shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

int draw_light_source(unsigned int shader, unsigned int VAO, Camera* camera) {
    glUseProgram(shader);
    glBindVertexArray(VAO);

    vec3 light_pos = { 1.2f, 1.0f, 2.0f };

    mat4 model, view, projection;

    glm_perspective(glm_rad(camera->zoom),
            (float)camera->screen_width / (float)camera->screen_height,
            0.1f, 100.0f, projection);
    int projection_loc = glGetUniformLocation(shader, "projection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float*)projection);

    camera_view_matrix(camera, view);
    int view_loc = glGetUniformLocation(shader, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float*)view);

    glm_mat4_identity(model);
    glm_translate(model, light_pos);
    glm_scale(model, (vec3){ 0.2f, 0.2f, 0.2f });
    int model_loc = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)model);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    return 0;
}

int draw_simple_cube(unsigned int shader, unsigned int VAO, Camera* camera,
        vec3 cube_pos) {
    glUseProgram(shader);
    glBindVertexArray(VAO);

    mat4 model, view, projection;

    glm_perspective(glm_rad(camera->zoom),
            (float)camera->screen_width / (float)camera->screen_height,
            0.1f, 100.0f, projection);
    int projection_loc = glGetUniformLocation(shader, "projection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, (float*)projection);

    camera_view_matrix(camera, view);
    int view_loc = glGetUniformLocation(shader, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float*)view);

    glm_mat4_identity(model);
    glm_translate(model, cube_pos);
    int model_loc = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)model);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    return 0;
}
