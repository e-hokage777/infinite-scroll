#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// outputs
out vec2 TexCoords;

// uniforms
uniform mat4 projection = mat4(1.0);
uniform mat4 model = mat4(1.0);

uniform vec2 uvTopLeft;
uniform vec2 uvBottomRight;

out VS_OUT {
    vec2 texCoords;
} vs_out;

void main() {
    vs_out.texCoords = mix(uvTopLeft, uvBottomRight, vec2(texCoords.x, 1.0 - texCoords.y));
    gl_Position = projection * model * vec4(pos, 1.0);

}