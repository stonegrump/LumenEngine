#version 450 core

layout (binding = 0) uniform sampler2D textureObj;

in vec2 uv;

out vec4 color;

void main(void){
    color = texture2D(textureObj, uv);
}