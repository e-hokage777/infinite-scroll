#version 330 core

// inputs
in VS_OUT {
    vec2 texCoords;
} frag_in;

// outputs
out vec4 FragColor;

uniform sampler2D textureSampler;

void main() {
    vec4 tex = texture2D(textureSampler, frag_in.texCoords);
    FragColor = tex;
}