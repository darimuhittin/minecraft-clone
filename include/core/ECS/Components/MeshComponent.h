#pragma once

#include "core/ECS/Component.h"
#include "core/Mesh.h"
#include "graphics/Shader.h"
#include <memory>

class MeshComponent : public Component {
public:
    MeshComponent(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const Shader& shader)
        : m_Mesh(std::make_unique<Mesh>(vertices, indices, shader))
    {}

    void AddTexture(const std::string& path, const std::string& type) {
        m_Mesh->AddTexture(path, type);
    }

    void Draw(Renderer& renderer, const glm::mat4& transform) const {
        m_Mesh->Draw(renderer, transform);
    }

private:
    std::unique_ptr<Mesh> m_Mesh;
}; 