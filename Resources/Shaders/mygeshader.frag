#version 410 core

uniform sampler2D diffuseSampler;

in vec2 texCoord;

out vec4 fragColor;
in vec4 colorIn;
void main(){
    fragColor = texture(diffuseSampler, texCoord);
}   