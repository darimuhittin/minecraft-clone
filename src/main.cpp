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
#include "core/ECS/Systems/PhysicsSystem.h"
#include "core/Primitives.h"
#include "core/Camera.h"
#include "core/MouseController.h"
#include "core/KeyboardController.h"
#include "core/BlockFactory.h"
#include "core/WorldGenerator.h"

// Function to collect block positions from entities
std::vector<glm::vec3> GetBlockPositions(const World& world) {
    std::vector<glm::vec3> positions;
    for (const auto& entity : world.GetEntities()) {
        auto transform = entity->GetComponent<TransformComponent>();
        if (transform) {
            positions.push_back(transform->GetPosition());
        }
    }
    return positions;
}

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
    glfwWindowHint(GLFW_SAMPLES, 4); // Enable 4x MSAA

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

    // Enable multisampling
    glEnable(GL_MULTISAMPLE);
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Create renderer and world
    Renderer renderer;
    World world;

    // Add systems
    world.AddSystem(std::make_unique<RenderSystem>(renderer));
    auto physicsSystem = std::make_unique<PhysicsSystem>();
    PhysicsSystem* physicsPtr = physicsSystem.get();
    world.AddSystem(std::move(physicsSystem));

    // Create shader program
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    // Generate the world
    WorldGenerator::GenerateFlat(world, shader, 16); // Generates a 16x16 flat world
    
    // Debug: Print all block positions
    auto positions = GetBlockPositions(world);
    std::cout << "\nBlock positions after generation:" << std::endl;
    for (const auto& pos : positions) {
        std::cout << "Block at: (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
    }
    
    // Create camera and controllers - spawn higher above blocks
    Camera camera(glm::vec3(0.0f, 100.0f, 3.0f)); // Spawn well above blocks at y=5
    camera.SetPhysicsSystem(physicsPtr);
    camera.SetWorldEntities(&world.GetEntities());
    
    MouseController mouseController(camera);
    KeyboardController keyboardController(camera);

    // Initialize mouse controller
    mouseController.Initialize(window);

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

        // Clear screen and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.Clear();

        // Update world
        world.Update(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

