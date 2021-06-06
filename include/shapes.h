#ifndef SHAPES_H
#define SHAPES_H

// #include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/camera.h"

unsigned int create_first_triangle();
unsigned int create_second_triangle();
unsigned int create_rectangle();
unsigned int create_rainbow_rect();
unsigned int create_cube();
int draw_moving_triangle(unsigned int shader, unsigned int VAO, float time);
int draw_static_triangle(unsigned int shader, unsigned int VAO);
int draw_textured_rectangle(unsigned int shader, unsigned int VAO, float mix_value);
int draw_transformed_rectangle(unsigned int shader, unsigned int VAO, float time);
int draw_julien(unsigned int shader, unsigned int VAO, Camera* camera, float time);
int draw_light_source(unsigned int shader, unsigned int VAO, Camera* camera);
int draw_simple_cube(unsigned int shader, unsigned int VAO, Camera* camera,
        vec3 cube_pos);

#endif // SHAPES_H
