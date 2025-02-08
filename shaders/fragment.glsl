#version 330 core
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D textureSide;
uniform sampler2D textureTop;
uniform sampler2D textureBottom;
uniform int faceIndex;  // 0: side, 1: top, 2: bottom
void main() {
    if (faceIndex == 1) {
        FragColor = texture(textureTop, TexCoord);
    } else if (faceIndex == 2) {
        FragColor = texture(textureBottom, TexCoord);
    } else {
        FragColor = texture(textureSide, TexCoord);
    }
} 