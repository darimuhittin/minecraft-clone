#pragma once

#include <glad/glad.h>
#include <vector>

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    
    void SetData(const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);
    template<typename T>
    void SetData(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
        SetData(data.data(), data.size() * sizeof(T), usage);
    }

private:
    GLuint m_RendererID;
}; 