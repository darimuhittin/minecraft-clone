#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "graphics/Shader.h"
#include "graphics/Renderer.h"
#include "core/ECS/World.h"
#include "core/ECS/Entity.h"
#include "core/ECS/Components/TransformComponent.h"
#include "core/ECS/Components/MeshComponent.h"
#include "core/ECS/Systems/RenderSystem.h"
#include "core/Primitives.h"
#include "core/Camera.h"
#include "core/MouseController.h"
#include "core/KeyboardController.h"

int main()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Minecraft Clone - Debug", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create camera and controllers
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    MouseController mouseController(camera);
    KeyboardController keyboardController(camera);

    // Initialize mouse controller
    mouseController.Initialize(window);

    // Create renderer and world
    Renderer renderer;
    World world;

    // Add render system
    world.AddSystem(std::make_unique<RenderSystem>(renderer));

    // Create shader program
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    // Create a block entity
    auto blockEntity = world.CreateEntity();
    auto transform = blockEntity->AddComponent<TransformComponent>(glm::vec3(0.0f));
    auto mesh = blockEntity->AddComponent<MeshComponent>(Primitives::GetCubeVerticesFlat(), Primitives::GetCubeIndices(), shader);
    mesh->AddTexture("textures/blocks/grass_side.png", "side");
    mesh->AddTexture("textures/blocks/grass_top.png", "top");
    mesh->AddTexture("textures/blocks/dirt.png", "bottom");

    // Set clear color
    renderer.SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Game loop
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        keyboardController.ProcessInput(window, deltaTime);

        // Update scene matrices
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        renderer.BeginScene(view, projection);

        // Clear screen
        renderer.Clear();

        // Update world
        world.Update(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

