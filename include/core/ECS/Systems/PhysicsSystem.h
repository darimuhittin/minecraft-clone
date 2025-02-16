#pragma once

#include "core/ECS/System.h"
#include <glm/glm.hpp>

class Camera;

class PhysicsSystem : public System {
public:
    PhysicsSystem();
    
    void Update(float deltaTime, const std::vector<std::shared_ptr<Entity>>& entities) override;
    
    // Camera physics interface
    glm::vec3 CalculateNewPosition(const glm::vec3& currentPos, const glm::vec3& moveDirection, 
                                  glm::vec3& velocity, float deltaTime,
                                  const std::vector<std::shared_ptr<Entity>>& entities);
    
    bool IsOnGround(const glm::vec3& position, const std::vector<std::shared_ptr<Entity>>& entities) const;
    void HandleJump(glm::vec3& velocity, bool isOnGround, bool& isJumping);
    
    // Physics constants (can be adjusted as needed)
    static constexpr float GRAVITY = -20.0f;  // Increased gravity for snappier jumps
    static constexpr float TERMINAL_VELOCITY = -30.0f;  // Increased terminal velocity
    static constexpr float JUMP_FORCE = 8.0f;  // Increased jump force
    static constexpr float PLAYER_HEIGHT = 1.8f;
    static constexpr float PLAYER_WIDTH = 0.6f;
    static constexpr float GROUND_OFFSET = 0.01f;

private:
    // Collision detection helpers
    bool CheckCollision(const glm::vec3& position, const std::vector<std::shared_ptr<Entity>>& entities) const;
    bool CheckAABBCollision(const glm::vec3& pos1, const glm::vec3& size1,
                           const glm::vec3& pos2, const glm::vec3& size2) const;
    glm::vec3 ApplyGravity(const glm::vec3& position, glm::vec3& velocity, float deltaTime) const;
}; 