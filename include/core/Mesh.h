#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>
#include <memory>
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/Renderer.h"

struct TextureInfo {
    std::shared_ptr<Texture> texture;
    std::string type;
};

class Mesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const Shader& shader);
    ~Mesh() = default;

    void Draw(Renderer& renderer, const glm::mat4& transform) const;
    void AddTexture(const std::string& path, const std::string& type);

private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_EBO;
    std::vector<TextureInfo> m_Textures;
    const Shader& m_DefaultShader;
}; 