#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define INFO_LOG_SIZE 512

char* read_file(const char* file_name);
unsigned int create_shader_program(const char* vert, const char* frag);

#endif // SHADER_H
