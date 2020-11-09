#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include "GraphicsLib.h"

#include "Renderer.h"

class Primitives {

public:
    static const GLfloat CubeVerticies[];
    static const GLfloat CubeColors[];
};

class Cube : Renderable {
public:
    Cube(glm::vec3 position, glm::vec3 scale, glm::mat4 transform, int shader, int id);
    ~Cube();
};