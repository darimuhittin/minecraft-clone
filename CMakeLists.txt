cmake_minimum_required(VERSION 3.10)
project(minecraft_clone)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add vcpkg toolchain file if not already set
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Create STB implementation source
file(WRITE ${CMAKE_BINARY_DIR}/stb_image_impl.cpp
    "#define STB_IMAGE_IMPLEMENTATION\n#include <stb_image.h>\n")

# Source files
set(SOURCES
    src/main.cpp
    src/core/Block.cpp
    src/core/GameObject.cpp
    src/core/Mesh.cpp
    src/core/Primitives.cpp
    src/core/Scene.cpp
    src/core/Camera.cpp
    src/core/MouseController.cpp
    src/core/KeyboardController.cpp
    src/graphics/IndexBuffer.cpp
    src/graphics/Renderer.cpp
    src/graphics/Shader.cpp
    src/graphics/Texture.cpp
    src/graphics/VertexArray.cpp
    src/graphics/VertexBuffer.cpp
    ${CMAKE_BINARY_DIR}/stb_image_impl.cpp
)

# Header files
file(GLOB_RECURSE HEADERS
    "${CMAKE_SOURCE_DIR}/include/*.h"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    glad::glad
    glm::glm
)

# Copy shader files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})

# Copy texture files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR}) 