#version 410 core
in vec4 colorIn;
in vec2 UV;
out vec4 fragmentColor;

void main() {
    fragmentColor = colorIn;
}