#include "Shader.h"

#include <GL/glew.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"



Shader::Shader(const std::string& filename) : m_FilePath(filename), m_RendererID(0){
    ShaderProgramSource source = ParseShader(filename);
    m_RendererID = CreateShader(source.VertexSource, source.GeometryShader, source.FragmentSource);
}

Shader::~Shader() {
    GLCALL(glDeleteProgram(m_RendererID));
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader) {
    GLCALL(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int gs = 0;
    if (!geometryShader.empty()) {
        gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);
    }
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //compiled shaders need to be linked to one program
    GLCALL(glAttachShader(program, vs));
    if (gs) {
        GLCALL(glAttachShader(program, gs));
    }
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    //shaders have been linked, so we can clean up some stuff
    GLCALL(glDeleteShader(vs));
    if (gs != -1) {
        GLCALL(glDeleteShader(gs));
    }
    GLCALL(glDeleteShader(fs));

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    GLCALL(unsigned int id = glCreateShader(type));
    //source string must exist at this point
    const char* src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        //This means an unsuccessful compile
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : (type == GL_GEOMETRY_SHADER ? "geometry" : "fragment")) << " shader: " << message << std::endl;
        GLCALL(glDeleteShader(id));

        return 0;
    }

    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);


    if (!stream.good()) {
      std::cout << "current path: " << std::filesystem::current_path() << std::endl;
      std::cout << "ERROR: attempted to load shader from nonexisting file: " << filepath << std::endl;
      return {"",""};
    }

    std::cout << "parsing shader: " << filepath << std::endl;

    enum class ShaderType {
        NONE = -1, VERTEX = 0, GEOMETRY = 1, FRAGMENT = 2
    };

    std::string line;
    std::stringstream ss[3];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
            else if (line.find("geometry") != std::string::npos) {
                type = ShaderType::GEOMETRY;
            }
        }
        else if (type != ShaderType::NONE) {

            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str(), ss[2].str() };
}

void Shader::Bind() const {
    GLCALL(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCALL(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 vector) {
    GLCALL(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
}

void Shader::SetUniform1i(const std::string& name, int value) {
    GLCALL(glUniform1i(GetUniformLocation(name), value));
}

//Make sure the shader is bound FIRST!!!!!!!
void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix) {
    GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist." << std::endl;
    m_UniformLocationCache[name] = location;
    return location;
}
