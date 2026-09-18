#version 330 core

in VS_OUT{
    vec3 position;
    vec3 normal;
    vec2 texCoords;
} frag_in;

out vec4 FragColor;


uniform sampler2D spriteSampler;

void main() {
    vec4 tex = texture2D(spriteSampler, frag_in.texCoords);
    FragColor = vec4(tex);
}