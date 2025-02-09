#pragma once

#include <vector>
#include <memory>
#include "core/GameObject.h"
#include "graphics/Renderer.h"

class Scene {
public:
    Scene();
    ~Scene() = default;

    void AddObject(std::shared_ptr<GameObject> object);
    void Update(float deltaTime);
    void Render(Renderer& renderer);

    void SetViewMatrix(const glm::mat4& viewMatrix) { m_ViewMatrix = viewMatrix; }
    void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

private:
    std::vector<std::shared_ptr<GameObject>> m_GameObjects;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
}; 