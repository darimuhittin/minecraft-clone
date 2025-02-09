#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Primitives {
    // Structure to hold vertex data
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    // Functions to get cube data
    std::vector<Vertex> GetCubeVertices();
    std::vector<unsigned int> GetCubeIndices();
    
    // Functions to get flattened vertex data (position, normal, texcoords as float array)
    std::vector<float> GetCubeVerticesFlat();
} 