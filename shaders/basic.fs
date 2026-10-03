#version 330 core


in VS_OUT{
    vec2 texCoords;
} frag_in;

out vec4 FragColor;

uniform sampler2D sampler;

void main(){
    vec4 texture = texture2D(sampler, frag_in.texCoords);
    FragColor = texture;
    // FragColor = vec4(1.0f, 0.1f, 0.1f, 1.0f);
}