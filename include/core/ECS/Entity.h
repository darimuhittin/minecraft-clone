#pragma once

#include <unordered_map>
#include <memory>
#include <typeindex>
#include "core/ECS/Component.h"

class Entity {
public:
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* componentPtr = component.get();
        componentPtr->SetOwner(this);
        m_Components[typeid(T)] = std::move(component);
        return componentPtr;
    }

    template<typename T>
    T* GetComponent() {
        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    template<typename T>
    bool HasComponent() {
        return m_Components.find(typeid(T)) != m_Components.end();
    }

    template<typename T>
    void RemoveComponent() {
        m_Components.erase(typeid(T));
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;
}; 