#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

// uniforms
uniform mat4 model;

out VS_OUT {
    vec2 texCoords;
} vs_out;

void main() {
    vs_out.texCoords = texCoords;
    gl_Position = model * vec4(pos, 1.0);
}