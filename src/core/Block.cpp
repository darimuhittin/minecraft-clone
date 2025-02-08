#include "core/Block.h"
#include "core/Primitives.h"

Block::Block(BlockType type, const glm::vec3& position)
    : type(type), position(position), mesh(Primitives::GetCubeVertices(), Primitives::GetCubeIndices())
{
    switch (type) {
        case BlockType::GRASS:
            mesh.AddTexture("textures/blocks/grass_side.png", "side");
            mesh.AddTexture("textures/blocks/grass_top.png", "top");
            mesh.AddTexture("textures/blocks/dirt.png", "bottom");
            break;
        // Add other block types here
    }
}

void Block::Draw(unsigned int shaderProgram) const {
    mesh.BindTextures();
    mesh.Draw(shaderProgram);
}

glm::vec3 Block::getPosition() const {
    return position;
}

