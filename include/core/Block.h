#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"

enum class BlockType {
    GRASS,
    DIRT,
    STONE
};

class Block {
public:
    Block(BlockType type, const glm::vec3& position);
    void Draw(unsigned int shaderProgram) const;
    glm::vec3 getPosition() const;
private:
    BlockType type;
    glm::vec3 position;
    Mesh mesh;
};

