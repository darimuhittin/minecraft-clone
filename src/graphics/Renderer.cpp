#include "graphics/Renderer.h"
#include <glad/glad.h>
#include <iostream>

Renderer::Renderer()
    : m_ViewMatrix(1.0f), m_ProjectionMatrix(1.0f)
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::BeginScene(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    m_ViewMatrix = viewMatrix;
    m_ProjectionMatrix = projectionMatrix;
}

void Renderer::EndScene()
{
    // Reset any state if needed
}

void Renderer::DrawMesh(const VertexArray& vertexArray, const IndexBuffer& indexBuffer,
                       const Shader& shader, const glm::mat4& transform)
{
    shader.Bind();
    shader.SetMat4("model", transform);
    shader.SetMat4("view", m_ViewMatrix);
    shader.SetMat4("projection", m_ProjectionMatrix);

    vertexArray.Bind();
    glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
    vertexArray.Unbind();
}

void Renderer::DrawTexturedMesh(const VertexArray& vertexArray, const IndexBuffer& indexBuffer,
                              const Shader& shader, const std::vector<std::shared_ptr<Texture>>& textures,
                              const glm::mat4& transform)
{
    shader.Bind();
    shader.SetMat4("model", transform);
    shader.SetMat4("view", m_ViewMatrix);
    shader.SetMat4("projection", m_ProjectionMatrix);

    // Bind all textures
    for (size_t i = 0; i < textures.size(); i++) {
        textures[i]->ActivateAndBind(i);
        shader.SetInt("textures[" + std::to_string(i) + "]", i);
    }

    vertexArray.Bind();
    
    // Draw each face with its corresponding texture
    // Each face has 6 indices (2 triangles)
    for (int face = 0; face < 6; face++) {
        shader.SetInt("faceIndex",getFaceTextureIndex(face));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(face * 6 * sizeof(unsigned int)));
    }

    vertexArray.Unbind();
}

// Add this helper function to map face index to texture index
int Renderer::getFaceTextureIndex(int face) {
    // Map each face to the appropriate texture:
    // Front/Back/Left/Right faces use side texture (0)
    // Top face uses top texture (1)
    // Bottom face uses bottom texture (2)
    switch(face) {
        case 0: // Front
        case 1: // Back
        case 4: // Right
        case 5: // Left
            return 0; // Side texture
        case 2: // Top
            return 1; // Top texture
        case 3: // Bottom
            return 2; // Bottom texture
        default:
            return 0;
    }
} 