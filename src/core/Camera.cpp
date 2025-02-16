#include "core/Camera.h"

Camera::Camera(glm::vec3 position) : 
    position(position),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(-90.0f),
    pitch(0.0f),
    baseMovementSpeed(0.05f),
    movementSpeed(0.05f),
    mouseSensitivity(0.1f),
    zoom(45.0f),
    velocity(glm::vec3(0.0f)),
    isOnGround(false),
    isJumping(false),
    physicsSystem(nullptr),
    worldEntities(nullptr)
{
    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void Camera::UpdateSpeed(GLFWwindow* window, float deltaTime) {
    movementSpeed = baseMovementSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        movementSpeed = baseMovementSpeed * 2.0f;
    }
}

void Camera::HandleJump(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        physicsSystem->HandleJump(velocity, isOnGround, isJumping);
    }
}

glm::vec3 Camera::CalculateNewPosition(const glm::vec3& moveDirection, float deltaTime) {
    if (!physicsSystem || !worldEntities) return position + moveDirection;
    
    return physicsSystem->CalculateNewPosition(position, moveDirection, velocity, deltaTime, *worldEntities);
}

void Camera::ProcessKeyboard(GLFWwindow* window, float deltaTime) {
    if (!physicsSystem || !worldEntities) return;

    UpdateSpeed(window, deltaTime);
    HandleJump(window);

    glm::vec3 moveDirection(0.0f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveDirection += front * movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveDirection -= front * movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveDirection -= glm::normalize(glm::cross(front, up)) * movementSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveDirection += glm::normalize(glm::cross(front, up)) * movementSpeed;

    // Remove vertical component from movement direction
    moveDirection.y = 0.0f;
    if (glm::length(moveDirection) > 0.0f) {
        moveDirection = glm::normalize(moveDirection) * movementSpeed;
    }

    position = CalculateNewPosition(moveDirection, deltaTime);
    isOnGround = physicsSystem->IsOnGround(position, *worldEntities);
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, position + front, up);
} 