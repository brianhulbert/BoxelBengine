#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLOGCALL(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLOGCALL(const char* function, const char* file, int line);

class Renderer {
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};

struct Transform {
    glm::vec3 translation;
    glm::vec3 rotation;
};