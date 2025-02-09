#pragma once

#include <GLFW/glfw3.h>
#include "core/Camera.h"

class MouseController {
public:
    MouseController(Camera& camera);
    void Initialize(GLFWwindow* window);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

private:
    static Camera* activeCamera;
    static bool firstMouse;
    static float lastX;
    static float lastY;
}; 