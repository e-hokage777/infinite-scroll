#version 330 core

// vertex attributes
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoords;

//outputs
out VS_OUT {
    vec2 texCoords;
} vs_out;


void main() {
    vs_out.texCoords = texCoords;
    gl_Position = vec4(pos, 1.0);
}