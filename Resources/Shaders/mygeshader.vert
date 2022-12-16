#version 410 core
//Default shader for MYGE
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoord;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

out vec3 surfaceNormal;
out vec2 texCoord;

void main(){
    texCoord = vertexTexCoord;

    surfaceNormal = vec3(1,1,1);

    gl_Position = pMatrix * vMatrix * mMatrix * vec4(vertexPosition, 1.0);
}