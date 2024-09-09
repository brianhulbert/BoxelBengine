#include "Material.h"

Material::Material(std::string textureFile, std::string shaderFile) : texture(new Texture(textureFile)), shader(new Shader(shaderFile)){
	this->Bind();
	this->SetUniform("u_Texture", 0);
}

Material::~Material() {
	delete texture;
	delete shader;
}

void Material::Bind() const{
	texture->Bind();
	shader->Bind();
}

void Material::SetUniform(std::string name, glm::mat4 value) {
	shader->SetUniformMat4f(name, value);
}

void Material::SetUniform(std::string name, int value) {
	shader->SetUniform1i(name, value);
}

void Material::SetUniform(std::string name, glm::vec3 value) {
	shader->SetUniform3f(name, value);
}