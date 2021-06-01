cmake_minimum_required(VERSION 3.20)

project(learn-opengl)
set(learn-opengl VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(glad/)

add_executable(learn-opengl
    src/main.c
    src/shader.c
    src/shapes.c
    src/textures.c
    include/shader.h
    include/textures.h
    include/shapes.h
    include/stb_image.h
)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(learn-opengl 
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(learn-opengl
    PRIVATE glad
    glfw
    OpenGL::GL
    m
    cglm
    ${CMAKE_DL_LIBS}
)
