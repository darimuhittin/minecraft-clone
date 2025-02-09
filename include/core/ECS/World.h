#pragma once

#include <vector>
#include <memory>
#include "core/ECS/Entity.h"
#include "core/ECS/System.h"

class World {
public:
    std::shared_ptr<Entity> CreateEntity() {
        auto entity = std::make_shared<Entity>();
        m_Entities.push_back(entity);
        return entity;
    }

    void AddSystem(std::unique_ptr<System> system) {
        m_Systems.push_back(std::move(system));
    }

    void Update(float deltaTime) {
        for (auto& system : m_Systems) {
            system->Update(deltaTime, m_Entities);
        }
    }

    const std::vector<std::shared_ptr<Entity>>& GetEntities() const {
        return m_Entities;
    }

private:
    std::vector<std::shared_ptr<Entity>> m_Entities;
    std::vector<std::unique_ptr<System>> m_Systems;
};