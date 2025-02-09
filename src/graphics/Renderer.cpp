#include "graphics/Renderer.h"
#include <glad/glad.h>

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

    for (size_t i = 0; i < textures.size(); i++) {
        textures[i]->Bind(i);
    }

    vertexArray.Bind();
    glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
    vertexArray.Unbind();
} 