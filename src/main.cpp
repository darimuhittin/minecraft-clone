#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Camera variables
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400.0f;
float lastY = 300.0f;
bool firstMouse = true;
float cameraSpeed = 0.0005f;

// Mouse callback function
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

// Process keyboard input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float currentSpeed = cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        currentSpeed *= 2.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += currentSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= currentSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * currentSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * currentSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraUp * currentSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos -= cameraUp * currentSpeed;
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

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Minecraft Clone - Debug", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set up mouse input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create vertex shader with camera transformation
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 TexCoord;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            TexCoord = aTexCoord;
        }
    )";

    // Create fragment shader with multiple textures
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec2 TexCoord;
        out vec4 FragColor;
        uniform sampler2D textureSide;
        uniform sampler2D textureTop;
        uniform sampler2D textureBottom;
        uniform int faceIndex;  // 0: side, 1: top, 2: bottom
        void main() {
            if (faceIndex == 1) {
                FragColor = texture(textureTop, TexCoord);
            } else if (faceIndex == 2) {
                FragColor = texture(textureBottom, TexCoord);
            } else {
                FragColor = texture(textureSide, TexCoord);
            }
        }
    )";

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create vertex data for cube
    float vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // top-left
        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-right
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-left
        // Left face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
        // Right face
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // top-left
        // Top face
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // bottom-right
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // top-right
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f   // top-left
    };

    unsigned int indices[] = {
        0,  1,  2,    2,  3,  0,   // Front face
        4,  5,  6,    6,  7,  4,   // Back face
        8,  9,  10,   10, 11, 8,   // Left face
        12, 13, 14,   14, 15, 12,  // Right face
        16, 17, 18,   18, 19, 16,  // Top face
        20, 21, 22,   22, 23, 20   // Bottom face
    };

    // Create buffers
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures
    unsigned int textureSide, textureTop, textureBottom;
    
    // Side texture (grass_side)
    glGenTextures(1, &textureSide);
    glBindTexture(GL_TEXTURE_2D, textureSide);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("textures/blocks/grass_side.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load grass side texture" << std::endl;
    }
    stbi_image_free(data);

    // Top texture (grass_top)
    glGenTextures(1, &textureTop);
    glBindTexture(GL_TEXTURE_2D, textureTop);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    data = stbi_load("textures/blocks/grass_top.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load grass top texture" << std::endl;
    }
    stbi_image_free(data);

    // Bottom texture (dirt)
    glGenTextures(1, &textureBottom);
    glBindTexture(GL_TEXTURE_2D, textureBottom);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    data = stbi_load("textures/blocks/dirt.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load dirt texture" << std::endl;
    }
    stbi_image_free(data);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Render loop
    float angle = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Set texture uniforms
        glUniform1i(glGetUniformLocation(shaderProgram, "textureSide"), 0);
        glUniform1i(glGetUniformLocation(shaderProgram, "textureTop"), 1);
        glUniform1i(glGetUniformLocation(shaderProgram, "textureBottom"), 2);

        // Create transformation matrices
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // Set matrix uniforms
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Bind textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureSide);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureTop);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textureBottom);

        // Draw cube faces with appropriate textures
        glBindVertexArray(VAO);
        
        // Draw sides (faces 0-3)
        glUniform1i(glGetUniformLocation(shaderProgram, "faceIndex"), 0);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        
        // Draw top face
        glUniform1i(glGetUniformLocation(shaderProgram, "faceIndex"), 1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));
        
        // Draw bottom face
        glUniform1i(glGetUniformLocation(shaderProgram, "faceIndex"), 2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

