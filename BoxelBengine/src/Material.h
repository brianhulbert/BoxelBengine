#pragma once

#include <string>
#include <stdexcept>
#include "Texture.h"
#include "Shader.h"

class Material {
public:
	Material(std::string textureFile, std::string shaderFile);
	~Material();
	void Bind() const;

	void SetUniform(std::string name, glm::mat4 value);
	void SetUniform(std::string name, int value);
	void SetUniform(std::string name, glm::vec3 value);
private:
	/*
	TODO:
	- Support runtime shader generation
	*/
	Texture* texture;
	Shader* shader;
};