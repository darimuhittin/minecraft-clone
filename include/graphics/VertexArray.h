#pragma once

#include <glad/glad.h>
#include <vector>
#include "graphics/VertexBuffer.h"

struct VertexBufferElement {
    GLenum type;
    unsigned int count;
    unsigned char normalized;
    
    static unsigned int GetSizeOfType(GLenum type) {
        switch (type) {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:  return sizeof(GLbyte);
        }
        return 0;
    }
};

class VertexBufferLayout {
public:
    VertexBufferLayout() : m_Stride(0) {}
    
    template<typename T>
    void Push(unsigned int count) {
        static_assert(false);
    }
    
    template<>
    void Push<float>(unsigned int count) {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }
    
    template<>
    void Push<unsigned int>(unsigned int count) {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }
    
    template<>
    void Push<unsigned char>(unsigned int count) {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
    
    inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
    
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
};

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
    GLuint m_RendererID;
}; 