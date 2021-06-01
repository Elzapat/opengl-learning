#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float horizontal_offset;
uniform float vertical_offset;

out vec3 ourColor;

void main() {
    gl_Position = vec4(aPos.x + horizontal_offset, aPos.y + vertical_offset, aPos.z, 1.0);
    ourColor = vec3(aPos.x + horizontal_offset, aPos.y + vertical_offset, aPos.z);
}
