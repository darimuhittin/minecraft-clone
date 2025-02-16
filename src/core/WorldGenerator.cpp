#include "core/WorldGenerator.h"
#include "core/BlockFactory.h"

void WorldGenerator::GenerateFlat(World& world, const Shader& shader, int size) {
    // Generate a flat world of size x size blocks
    for (int x = -size/2; x < size/2; x++) {
        for (int z = -size/2; z < size/2; z++) {
            // Create grass layer
            BlockFactory::CreateBlock(world, BlockType::GRASS, 
                glm::vec3(x, 0, z), shader);
            
            // Create dirt layers beneath
            for (int y = -1; y > -3; y--) {
                BlockFactory::CreateBlock(world, BlockType::DIRT, 
                    glm::vec3(x, y, z), shader);
            }
            
            // Create stone layer at bottom
            BlockFactory::CreateBlock(world, BlockType::STONE, 
                glm::vec3(x, -3, z), shader);
        }
    }
}

void WorldGenerator::GenerateChunk(World& world, const Shader& shader, 
                                 const glm::ivec2& chunkPos, int chunkSize) {
    glm::ivec2 worldPos = chunkPos * chunkSize;
    
    for (int x = 0; x < chunkSize; x++) {
        for (int z = 0; z < chunkSize; z++) {
            int worldX = worldPos.x + x;
            int worldZ = worldPos.y + z;
            
            float height = GetHeight(worldX, worldZ);
            
            // Create grass block at surface
            BlockFactory::CreateBlock(world, BlockType::GRASS,
                glm::vec3(worldX, height, worldZ), shader);
                
            // Fill below surface with dirt and stone
            for (int y = height - 1; y > height - 4; y--) {
                BlockFactory::CreateBlock(world, BlockType::DIRT,
                    glm::vec3(worldX, y, worldZ), shader);
            }
            
            for (int y = height - 4; y > height - 5; y--) {
                BlockFactory::CreateBlock(world, BlockType::STONE,
                    glm::vec3(worldX, y, worldZ), shader);
            }
        }
    }
}

float WorldGenerator::GetHeight(int x, int z) {
    // For now, return 0 for flat terrain
    // Later, you can implement noise functions here for more interesting terrain
    return 0.0f;
} 