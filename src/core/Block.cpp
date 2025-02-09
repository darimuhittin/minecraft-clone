#include "core/Block.h"
#include "core/Primitives.h"

Block::Block(BlockType type, const glm::vec3& position, const Shader& shader)
    : GameObject(position)
    , m_Type(type)
    , m_Mesh(Primitives::GetCubeVerticesFlat(), Primitives::GetCubeIndices(), shader)
{
    switch (type) {
        case BlockType::GRASS:
            m_Mesh.AddTexture("textures/blocks/grass_side.png", "side");
            m_Mesh.AddTexture("textures/blocks/grass_top.png", "top");
            m_Mesh.AddTexture("textures/blocks/dirt.png", "bottom");
            break;
        // Add other block types here
    }
}

void Block::Update(float deltaTime)
{
    // Add any block-specific update logic here
}

void Block::Render(Renderer& renderer)
{
    m_Mesh.Draw(renderer, GetTransform());
} 