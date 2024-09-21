#pragma once

#include <GL/glew.h>

#include <iostream>

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Material.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    void Draw(const VertexArray& va, const IndexBuffer& ib, Material& material) const;
    void Clear() const;
};

struct Transform {
    glm::vec3 translation;
    glm::vec3 rotation;

    glm::mat4 GetMat() { 
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        return glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    };
};

