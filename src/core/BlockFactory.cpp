#include "core/BlockFactory.h"
#include "core/Primitives.h"

std::shared_ptr<Entity> BlockFactory::CreateBlock(World& world, BlockType type, 
                                                const glm::vec3& position, 
                                                const Shader& shader) 
{
    auto entity = world.CreateEntity();
    entity->AddComponent<TransformComponent>(position);
    auto mesh = entity->AddComponent<MeshComponent>(
        Primitives::GetCubeVerticesFlat(), 
        Primitives::GetCubeIndices(), 
        shader
    );
    
    SetupBlockTextures(mesh, type);
    return entity;
}

void BlockFactory::SetupBlockTextures(MeshComponent* mesh, BlockType type) 
{
    switch (type) {
        case BlockType::GRASS:
            mesh->AddTexture("textures/blocks/grass_side_processed.png", "side");
            mesh->AddTexture("textures/blocks/grass_top_processed.png", "top");
            mesh->AddTexture("textures/blocks/dirt_processed.png", "bottom");
            break;
            
        case BlockType::DIRT:
            mesh->AddTexture("textures/blocks/dirt_processed.png", "side");
            mesh->AddTexture("textures/blocks/dirt_processed.png", "top");
            mesh->AddTexture("textures/blocks/dirt_processed.png", "bottom");
            break;
            
        case BlockType::STONE:
            mesh->AddTexture("textures/blocks/stone_processed.png", "side");
            mesh->AddTexture("textures/blocks/stone_processed.png", "top");
            mesh->AddTexture("textures/blocks/stone_processed.png", "bottom");
            break;
    }
} 