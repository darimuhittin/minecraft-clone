#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "graphics/Shader.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Texture.h"

class Renderer {
public:
    Renderer();
    ~Renderer() = default;

    void Clear() const;
    void SetClearColor(float r, float g, float b, float a);
    
    void BeginScene(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void EndScene();

    void DrawMesh(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, 
                 const Shader& shader, const glm::mat4& transform);
    
    void DrawTexturedMesh(const VertexArray& vertexArray, const IndexBuffer& indexBuffer,
                         const Shader& shader, const std::vector<std::shared_ptr<Texture>>& textures,
                         const glm::mat4& transform);

    int getFaceTextureIndex(int face);

private:
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
}; 