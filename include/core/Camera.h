#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include "core/ECS/Systems/PhysicsSystem.h"
#include "core/ECS/Entity.h"

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));

    void UpdateCameraVectors();
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessKeyboard(GLFWwindow* window, float deltaTime);
    glm::mat4 GetViewMatrix() const;

    // Getters
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetFront() const { return front; }
    glm::vec3 GetUp() const { return up; }

    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler angles
    float yaw;
    float pitch;

    // Camera options
    float baseMovementSpeed;  // Base movement speed
    float movementSpeed;      // Current movement speed
    float mouseSensitivity;
    float zoom;

    // Physics attributes
    glm::vec3 velocity;
    bool isOnGround;
    bool isJumping;

    // Physics system
    void SetPhysicsSystem(PhysicsSystem* physics) { physicsSystem = physics; }
    void SetWorldEntities(const std::vector<std::shared_ptr<Entity>>* entities) { worldEntities = entities; }

private:
    void UpdateSpeed(GLFWwindow* window, float deltaTime);
    void HandleJump(GLFWwindow* window);
    glm::vec3 CalculateNewPosition(const glm::vec3& moveDirection, float deltaTime);
    
    PhysicsSystem* physicsSystem;
    const std::vector<std::shared_ptr<Entity>>* worldEntities;
}; 