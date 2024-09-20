#include <memory>
#include <array>
#include <cmath> 

#include "GameObject.h"
#include "GameWindow.h"
#include "scenes/Scene.h"

GameObject::GameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile, VertexArray* va, VertexBuffer* vb, IndexBuffer* ib) :
	parentScene(parentScene), mesh(mesh), shader(nullptr), texture(nullptr), va(va), vb(vb), ib(ib),
	isVisible(false), updateTransformUniform(false), transform({glm::vec3(0.0f), glm::vec3(0.0f) }), velocity({ glm::vec3(0.0f), glm::vec3(0.0f) }), isDestructable(true) {
	if (!vb) {
		this->vb = new VertexBuffer(mesh->GetVertexData(), mesh->GetVertexCount() * mesh->GetVertexSize());
	}
	if (!va) {
		this->va = new VertexArray();
		this->va->AddBuffer(*this->vb, *mesh->GetVertexLayout());
	}
	if (!ib) {
		this->ib = new IndexBuffer(mesh->GetIndexData(), mesh->GetIndexCount());
	}

	//create shader
	shader = new Shader(shaderfile);
	shader->Bind();

	//create texture and set shader uniform
	texture = new Texture(texturefile);
	//Set uniforms
	shader->SetUniform1i("u_Texture", 0);

	isVisible = true;
}

GameObject::~GameObject() {
	if (isDestructable) {
		delete va;
		delete vb;
		delete ib;
		delete shader;
		delete mesh;
	}
}

void GameObject::Draw() {
	if (isVisible) {
		shader->Bind();
		va->Bind();
		ib->Bind();

		glm::mat4 model = GetModelMat();
		glm::mat4 view = parentScene->GetViewMat();
		glm::mat4 proj = parentScene->GetProjMat();
		glm::mat4 MVP = proj * view * model;

		shader->SetUniformMat4f("u_MVP", MVP);
		texture->Bind();
		renderer.Draw(*va, *ib, *shader);
	}
}

void GameObject::Update(float deltaTime) {
	//std::cout << "delatTime: " << deltaTime << std::endl;
	transform.translation += deltaTime * velocity.transVelocity;
	transform.rotation.x = std::fmodf((deltaTime * velocity.rotVelocity.x) + transform.rotation.x, 360.0f);
	transform.rotation.y = std::fmodf((deltaTime * velocity.rotVelocity.y) + transform.rotation.y, 360.0f);
	transform.rotation.z = std::fmodf((deltaTime * velocity.rotVelocity.z) + transform.rotation.z, 360.0f);
}

glm::mat4 GameObject::GetModelMat() {
	glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.translation);
	model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
	return glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
}

void GameObject::SetIndestructable() {
	isDestructable = false;
}
