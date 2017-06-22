#version 450 core

layout (location = 0) in vec4 position;

uniform mat4 projMat;
uniform mat4 tranMat;

out vec4 fsColor;

void main(void){
    gl_Position = projMat * tranMat * position;
    fsColor = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}