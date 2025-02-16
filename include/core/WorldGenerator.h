#pragma once

#include "core/ECS/World.h"
#include "graphics/Shader.h"
#include <glm/glm.hpp>

class WorldGenerator {
public:
    static void GenerateFlat(World& world, const Shader& shader, int size = 16);
    static void GenerateChunk(World& world, const Shader& shader, 
                            const glm::ivec2& chunkPos, 
                            int chunkSize = 16);
private:
    static float GetHeight(int x, int z); // For future terrain generation
}; 