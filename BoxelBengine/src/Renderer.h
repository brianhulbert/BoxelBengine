#pragma once

#include <GL/glew.h>

#include <iostream>

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <signal.h>

//#define ASSERT(x) if(!(x)) (raise(SIGTRAP));
//#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLOGCALL(#x, __FILE__, __LINE__));
#define GLCALL(x) x;
//replace with no-op for debugging purposes, should fix tho

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
