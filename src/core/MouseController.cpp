#include "core/MouseController.h"

Camera* MouseController::activeCamera = nullptr;
bool MouseController::firstMouse = true;
float MouseController::lastX = 400.0f;
float MouseController::lastY = 300.0f;

MouseController::MouseController(Camera& camera) {
    activeCamera = &camera;
}

void MouseController::Initialize(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseCallback);
}

void MouseController::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (!activeCamera) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    activeCamera->ProcessMouseMovement(xoffset, yoffset);
} 