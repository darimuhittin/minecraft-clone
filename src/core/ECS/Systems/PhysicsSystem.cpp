#include "core/ECS/Systems/PhysicsSystem.h"
#include "core/ECS/Components/TransformComponent.h"
#include <algorithm>

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::Update(float deltaTime, const std::vector<std::shared_ptr<Entity>>& entities) {
    // In the future, this will handle physics for all entities with physics components
    // For now, we're only handling player physics through the Camera interface
}

bool PhysicsSystem::CheckAABBCollision(const glm::vec3& pos1, const glm::vec3& size1,
                                     const glm::vec3& pos2, const glm::vec3& size2) const {
    return (pos1.x < pos2.x + size2.x &&
            pos1.x + size1.x > pos2.x &&
            pos1.y < pos2.y + size2.y &&
            pos1.y + size1.y > pos2.y &&
            pos1.z < pos2.z + size2.z &&
            pos1.z + size1.z > pos2.z);
}

bool PhysicsSystem::CheckCollision(const glm::vec3& position, 
                                 const std::vector<std::shared_ptr<Entity>>& entities) const {
    glm::vec3 playerSize(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_WIDTH);
    
    for (const auto& entity : entities) {
        auto transform = entity->GetComponent<TransformComponent>();
        if (transform) {
            if (CheckAABBCollision(position, playerSize, transform->GetPosition(), glm::vec3(1.0f))) {
                return true;
            }
        }
    }
    return false;
}

glm::vec3 PhysicsSystem::ApplyGravity(const glm::vec3& position, glm::vec3& velocity, float deltaTime) const {
    velocity.y += GRAVITY * deltaTime;
    velocity.y = std::max(velocity.y, TERMINAL_VELOCITY);
    
    glm::vec3 newPosition = position;
    newPosition.y += velocity.y * deltaTime;
    
    return newPosition;
}

bool PhysicsSystem::IsOnGround(const glm::vec3& position, 
                              const std::vector<std::shared_ptr<Entity>>& entities) const {
    glm::vec3 checkPos = position;
    checkPos.y -= GROUND_OFFSET;
    return CheckCollision(checkPos, entities);
}

void PhysicsSystem::HandleJump(glm::vec3& velocity, bool isOnGround, bool& isJumping) {
    if (isOnGround) {
        velocity.y = JUMP_FORCE;
        isJumping = true;
    } else if (!isOnGround && velocity.y < 0) {
        // Reset jumping state when falling
        isJumping = false;
    }
}

glm::vec3 PhysicsSystem::CalculateNewPosition(const glm::vec3& currentPos, const glm::vec3& moveDirection,
                                            glm::vec3& velocity, float deltaTime,
                                            const std::vector<std::shared_ptr<Entity>>& entities) {
    glm::vec3 newPosition = currentPos;
    
    // First apply horizontal movement
    glm::vec3 horizontalMove = moveDirection;
    horizontalMove.y = 0.0f; // Only consider X and Z movement
    newPosition += horizontalMove;
    
    // Check horizontal collisions and slide if needed
    if (CheckCollision(newPosition, entities)) {
        // Try to slide along the walls
        newPosition = currentPos;
        if (moveDirection.x != 0.0f) {
            newPosition.x += moveDirection.x;
            if (CheckCollision(newPosition, entities)) {
                newPosition.x = currentPos.x;
            }
        }
        if (moveDirection.z != 0.0f) {
            newPosition.z += moveDirection.z;
            if (CheckCollision(newPosition, entities)) {
                newPosition.z = currentPos.z;
            }
        }
    }
    
    // Then apply vertical movement (gravity)
    bool wasOnGround = IsOnGround(currentPos, entities);
    
    // Always apply gravity unless we're on the ground with no upward velocity
    if (!wasOnGround || velocity.y > 0) {
        velocity.y += GRAVITY * deltaTime;
        velocity.y = std::max(velocity.y, TERMINAL_VELOCITY);
    }
    
    // Apply vertical movement
    newPosition.y += velocity.y * deltaTime;
    
    // Check if we're on ground after vertical movement
    bool isOnGround = IsOnGround(newPosition, entities);
    
    // Handle landing
    if (isOnGround && velocity.y <= 0) {
        velocity.y = 0.0f;
        // Snap to ground more gently
        newPosition.y = std::ceil(newPosition.y - GROUND_OFFSET) + GROUND_OFFSET;
    }
    
    // Final collision check
    if (CheckCollision(newPosition, entities)) {
        if (velocity.y < 0) {
            // If we're moving down and collide, we've hit the ground
            velocity.y = 0.0f;
            newPosition.y = std::ceil(currentPos.y - GROUND_OFFSET) + GROUND_OFFSET;
            isOnGround = true;
        } else if (velocity.y > 0) {
            // If we're moving up and collide, we've hit the ceiling
            velocity.y = 0.0f;
            newPosition.y = currentPos.y;
        }
    }
    
    return newPosition;
} 