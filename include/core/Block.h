#pragma once

#include <glm/glm.hpp>
#include "core/GameObject.h"
#include "core/Mesh.h"
#include "graphics/Shader.h"

enum class BlockType {
    GRASS,
    DIRT,
    STONE
};

class Block : public GameObject {
public:
    Block(BlockType type, const glm::vec3& position, const Shader& shader);
    virtual ~Block() = default;
    
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer& renderer) override;

private:
    BlockType m_Type;
    Mesh m_Mesh;
}; 