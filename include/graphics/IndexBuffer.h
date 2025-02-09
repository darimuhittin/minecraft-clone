#pragma once

#include <glad/glad.h>
#include <vector>

class IndexBuffer {
public:
    IndexBuffer();
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    
    void SetData(const unsigned int* data, unsigned int count, GLenum usage = GL_STATIC_DRAW);
    void SetData(const std::vector<unsigned int>& data, GLenum usage = GL_STATIC_DRAW);
    
    unsigned int GetCount() const { return m_Count; }

private:
    GLuint m_RendererID;
    unsigned int m_Count;
}; 