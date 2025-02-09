#pragma once

#include "core/ECS/System.h"
#include "core/ECS/Components/TransformComponent.h"
#include "core/ECS/Components/MeshComponent.h"
#include "graphics/Renderer.h"

class RenderSystem : public System {
public:
    RenderSystem(Renderer& renderer) : m_Renderer(renderer) {}

    void Update(float deltaTime, const std::vector<std::shared_ptr<Entity>>& entities) override {
        for (const auto& entity : entities) {
            auto transform = entity->GetComponent<TransformComponent>();
            auto mesh = entity->GetComponent<MeshComponent>();

            if (transform && mesh) {
                mesh->Draw(m_Renderer, transform->GetTransformMatrix());
            }
        }
    }

private:
    Renderer& m_Renderer;
}; 