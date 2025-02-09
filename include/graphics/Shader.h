#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Uniform setters
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetMat4(const std::string& name, const glm::mat4& value) const;

    GLuint GetRendererID() const;

private:
    std::string LoadShaderSource(const std::string& shaderPath) const;
    GLuint CompileShader(const std::string& source, GLenum type) const;
    void CheckCompileErrors(GLuint shader, const std::string& type) const;
    GLint GetUniformLocation(const std::string& name) const;

    GLuint m_RendererID;
    mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
}; 