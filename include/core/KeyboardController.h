#pragma once

#include <GLFW/glfw3.h>
#include "core/Camera.h"

class KeyboardController {
public:
    KeyboardController(Camera& camera);
    void ProcessInput(GLFWwindow* window, float deltaTime);

private:
    Camera* camera;
}; 