#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uvs;

out vec2 uv;

uniform mat4 projMat;
uniform mat4 tranMat;

out vec4 fsColor;

void main(void){
    gl_Position = projMat * tranMat * position;
    fsColor = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
    uv = uvs;
}