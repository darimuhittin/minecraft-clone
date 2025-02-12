#include "core/Mesh.h"
#include <iostream>

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const Shader& shader)
    : m_DefaultShader(shader)
{
    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>();
    m_EBO = std::make_unique<IndexBuffer>();

    m_VAO->Bind();
    
    // Set vertex buffer data
    m_VBO->SetData(vertices);
    
    // Set index buffer data
    m_EBO->SetData(indices);

    // Set up vertex attributes
    VertexBufferLayout layout;
    layout.PushFloat(3); // Position
    layout.PushFloat(3); // Normal
    layout.PushFloat(2); // Texture coordinates
    m_VAO->AddBuffer(*m_VBO, layout);
}

void Mesh::Draw(Renderer& renderer, const glm::mat4& transform) const
{
    if (m_Textures.empty()) {
        // If no textures, use a default shader
        renderer.DrawMesh(*m_VAO, *m_EBO, m_DefaultShader, transform);
        return;
    }

    std::vector<std::shared_ptr<Texture>> textures;
    for (const auto& textureInfo : m_Textures) {
        textures.push_back(textureInfo.texture);
    }

    renderer.DrawTexturedMesh(*m_VAO, *m_EBO, m_DefaultShader, textures, transform);
}

void Mesh::AddTexture(const std::string& path, const std::string& type)
{
    TextureInfo textureInfo;
    textureInfo.texture = std::make_shared<Texture>(path);
    textureInfo.type = type;
    m_Textures.push_back(textureInfo);
} 