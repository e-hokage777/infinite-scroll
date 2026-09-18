#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;


out VS_OUT {
    vec3 position;
    vec3 normal;
    vec2 texCoords;
} vs_out;

uniform mat4 model = mat4(1.0);


void main() {
    vs_out.position = vec3(model * vec4(position, 1));
    vs_out.normal = normal;
    vs_out.texCoords = texCoords;

    gl_Position = model * vec4(position, 1.0);
}