#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D textures[3];  // Array of textures [side, top, bottom]
uniform int faceIndex;          // 0: side, 1: top, 2: bottom

void main() {
    FragColor = texture(textures[faceIndex], TexCoord);
} 