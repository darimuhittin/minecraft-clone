#pragma once

#include <cstdint>

// Forward declarations
class Entity;

class Component {
public:
    virtual ~Component() = default;
    
    void SetOwner(Entity* entity) { m_Owner = entity; }
    Entity* GetOwner() const { return m_Owner; }

private:
    Entity* m_Owner = nullptr;
}; 