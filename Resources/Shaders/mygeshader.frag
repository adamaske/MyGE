#version 410 core

uniform sampler2D diffuseSampler;

in vec3 surfaceNormal;
in vec2 texCoord;

out vec4 fragColor;

void main(){
    fragColor = vec4(1,1,1,1);
}