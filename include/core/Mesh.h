#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw(unsigned int shaderProgram) const;
    void AddTexture(const std::string& path, const std::string& type);
    void BindTextures() const;

private:
    unsigned int VAO, VBO, EBO;
    size_t indexCount;
    std::vector<Texture> textures;

    void setupMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    unsigned int loadTexture(const std::string& path);
}; 