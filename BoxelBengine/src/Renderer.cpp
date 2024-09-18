#include "Renderer.h"
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLOGCALL(const char* function, const char* file, int line) {
    //Error codes can be found in the glew header file
    //TODO: Translate error code to txt
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Material& material) const {
    va.Bind();
    ib.Bind();
    material.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ib.m_Count, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}