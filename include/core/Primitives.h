#pragma once
#include <vector>

class Primitives {
public:
    static const std::vector<float>& GetCubeVertices();
    static const std::vector<unsigned int>& GetCubeIndices();

private:
    static std::vector<float> cubeVertices;
    static std::vector<unsigned int> cubeIndices;
    static void InitializeCube();
    static bool initialized;
}; 