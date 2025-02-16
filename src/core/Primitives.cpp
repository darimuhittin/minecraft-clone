#include "core/Primitives.h"

namespace Primitives {
    std::vector<Vertex> GetCubeVertices() {
        std::vector<Vertex> vertices = {
            // Front face
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.001f, 0.001f}},  // Bottom-left
            {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.999f, 0.001f}},  // Bottom-right
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.999f, 0.999f}},  // Top-right
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.001f, 0.999f}},  // Top-left

            // Back face
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.001f, 0.001f}}, // Bottom-left
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.999f, 0.001f}}, // Bottom-right
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.999f, 0.999f}}, // Top-right
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.001f, 0.999f}}, // Top-left

            // Top face
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.001f, 0.001f}},  // Bottom-left
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.999f, 0.001f}},  // Bottom-right
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.999f, 0.999f}},  // Top-right
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.001f, 0.999f}},  // Top-left

            // Bottom face
            {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.001f, 0.001f}}, // Bottom-left
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.999f, 0.001f}}, // Bottom-right
            {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.999f, 0.999f}}, // Top-right
            {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.001f, 0.999f}}, // Top-left

            // Right face
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.001f, 0.001f}},  // Bottom-left
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.999f, 0.001f}},  // Bottom-right
            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.999f, 0.999f}},  // Top-right
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.001f, 0.999f}},  // Top-left

            // Left face
            {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.001f, 0.001f}}, // Bottom-left
            {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.999f, 0.001f}}, // Bottom-right
            {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.999f, 0.999f}}, // Top-right
            {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.001f, 0.999f}}  // Top-left
        };
        return vertices;
    }

    std::vector<unsigned int> GetCubeIndices() {
        std::vector<unsigned int> indices = {
            // Front face
            0, 1, 2,
            2, 3, 0,
            // Back face
            4, 5, 6,
            6, 7, 4,
            // Top face
            8, 9, 10,
            10, 11, 8,
            // Bottom face
            12, 13, 14,
            14, 15, 12,
            // Right face
            16, 17, 18,
            18, 19, 16,
            // Left face
            20, 21, 22,
            22, 23, 20
        };
        return indices;
    }

    std::vector<float> GetCubeVerticesFlat() {
        std::vector<float> flatVertices;
        auto vertices = GetCubeVertices();
        
        // Reserve space for all vertices (8 floats per vertex: 3 for pos, 3 for normal, 2 for texcoords)
        flatVertices.reserve(vertices.size() * 8);
        
        for (const auto& vertex : vertices) {
            // Position
            flatVertices.push_back(vertex.position.x);
            flatVertices.push_back(vertex.position.y);
            flatVertices.push_back(vertex.position.z);
            
            // Normal
            flatVertices.push_back(vertex.normal.x);
            flatVertices.push_back(vertex.normal.y);
            flatVertices.push_back(vertex.normal.z);
            
            // Texture coordinates
            flatVertices.push_back(vertex.texCoords.x);
            flatVertices.push_back(vertex.texCoords.y);
        }
        
        return flatVertices;
    }
} 