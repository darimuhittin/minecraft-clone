#include "core/Scene.h"

Scene::Scene()
    : m_ViewMatrix(1.0f)
    , m_ProjectionMatrix(1.0f)
{
}

void Scene::AddObject(std::shared_ptr<GameObject> object)
{
    m_GameObjects.push_back(object);
}

void Scene::Update(float deltaTime)
{
    for (auto& object : m_GameObjects) {
        object->Update(deltaTime);
    }
}

void Scene::Render(Renderer& renderer)
{
    renderer.BeginScene(m_ViewMatrix, m_ProjectionMatrix);
    
    for (auto& object : m_GameObjects) {
        object->Render(renderer);
    }
    
    renderer.EndScene();
} 