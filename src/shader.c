#include "../include/shader.h"

char* read_file(const char* file_name) {
    char* buffer = NULL;
    long length;
    FILE* fp = fopen(file_name, "rb");

    if (!fp) {
        printf("Error reading file %s\n", file_name);
        exit(-1);
    }

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = malloc(length + 1);
    if (buffer)
        fread(buffer, sizeof(char), length, fp);

    fclose(fp);

    buffer[length] = '\0';
    return buffer;
}

unsigned int create_shader_program(const char* vert, const char* frag) {
    int success;
    char info_log[INFO_LOG_SIZE];
    unsigned int vertex_shader;
    unsigned int fragment_shader;
    const char* vert_source = NULL;
    const char* frag_source = NULL;

    vert_source = read_file(vert);
    frag_source = read_file(frag);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vert_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, INFO_LOG_SIZE, NULL, info_log);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", info_log);
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, INFO_LOG_SIZE, NULL, info_log);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", info_log);
    }

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, INFO_LOG_SIZE, NULL, info_log);
        printf("ERROR::PROGRAM::LINK::FAILED\n%s", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}
