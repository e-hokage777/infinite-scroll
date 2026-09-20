#version 330 core

in VS_OUT {
    vec2 texCoords;
} frag_in;

out vec4 FragColor;

uniform float xOffset = 0;
uniform float yOffset = 0;
uniform sampler2D sampler;

void main() {
    // vec3 texture = vec3(texture2D(sampler, frag_in.texCoords));
    // FragColor = vec4(texture, 1.0);
    FragColor = texture2D(sampler, frag_in.texCoords + vec2(xOffset, yOffset));
}