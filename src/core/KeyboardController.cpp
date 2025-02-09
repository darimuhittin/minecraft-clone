#include "core/KeyboardController.h"

KeyboardController::KeyboardController(Camera& camera) : camera(&camera) {}

void KeyboardController::ProcessInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    camera->ProcessKeyboard(window, deltaTime);
} 