#pragma once

#include "core/ECS/World.h"
#include "core/ECS/Entity.h"
#include "core/ECS/Components/TransformComponent.h"
#include "core/ECS/Components/MeshComponent.h"
#include "graphics/Shader.h"
#include <memory>

enum class BlockType {
    GRASS,
    DIRT,
    STONE
    // Add more block types as needed
};

class BlockFactory {
public:
    static std::shared_ptr<Entity> CreateBlock(World& world, BlockType type, 
                                             const glm::vec3& position, 
                                             const Shader& shader);

private:
    static void SetupBlockTextures(MeshComponent* mesh, BlockType type);
}; 