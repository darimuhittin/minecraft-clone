#include "core/Primitives.h"

bool Primitives::initialized = false;
std::vector<float> Primitives::cubeVertices;
std::vector<unsigned int> Primitives::cubeIndices;

const std::vector<float>& Primitives::GetCubeVertices() {
    if (!initialized) {
        InitializeCube();
    }
    return cubeVertices;
}

const std::vector<unsigned int>& Primitives::GetCubeIndices() {
    if (!initialized) {
        InitializeCube();
    }
    return cubeIndices;
}

void Primitives::InitializeCube() {
    cubeVertices = {
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // top-left
        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-right
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-left
        // Left face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
        // Right face
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // top-left
        // Top face
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // top-right
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f   // top-left
    };

    cubeIndices = {
        0,  1,  2,    2,  3,  0,   // Front face
        4,  5,  6,    6,  7,  4,   // Back face
        8,  9,  10,   10, 11, 8,   // Left face
        12, 13, 14,   14, 15, 12,  // Right face
        16, 17, 18,   18, 19, 16,  // Top face
        20, 21, 22,   22, 23, 20   // Bottom face
    };

    initialized = true;
} 