#pragma once

#include <vector>
#include <memory>
#include "core/ECS/Entity.h"

class System {
public:
    virtual ~System() = default;
    virtual void Update(float deltaTime, const std::vector<std::shared_ptr<Entity>>& entities) = 0;
}; 