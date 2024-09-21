#include "InstancedGameObject.h"
#include "Renderer.h"
#include "Texture.h"

InstancedGameObject::InstancedGameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile, unsigned int count, glm::mat4* modelMatrices, VertexArray* va, VertexBuffer* vb, IndexBuffer* ib) :
	GameObject(parentScene, mesh, shaderfile, texturefile, va, vb, ib), count(count), modelMats(modelMatrices) {
	name = "Instanced Object";

	unsigned int modelBufferSize = count * sizeof(glm::mat4);
	transformVB = new VertexBuffer(modelMats, modelBufferSize);
	VertexBufferLayout modelBufferLayout;
	//modelBufferLayout.Push<glm::mat4>(1);
  modelBufferLayout.push_glmmat4(1);
	this->va->AddBuffer(*transformVB, modelBufferLayout, 1);
}

InstancedGameObject::~InstancedGameObject() {
	free(modelMats);
	delete transformVB;
}

InstancedGameObject* InstancedGameObject::CreateInstancedGameObject(scene::Scene* parentScene, Mesh* mesh, unsigned int count, glm::mat4* modelMatrices) {
	return new InstancedGameObject(parentScene, mesh, "res/shaders/BasicInstance.shader", "res/textures/cat.png", count, modelMatrices);
}

InstancedGameObject* InstancedGameObject::CreateInstancedGameObject(GameObject* obj, unsigned int count, Transform* transforms) {
	//Fix the texture issue
	obj->SetIndestructable();

	//Create a buffer to hold the model matrices
	glm::mat4* modelMats = (glm::mat4*)malloc(sizeof(glm::mat4) * count);
	for (unsigned int i = 0; i < count; i++) {
		modelMats[i] = transforms[i].GetMat();
	}

	free(transforms);

	return new InstancedGameObject(obj->parentScene, obj->mesh, "res/shaders/BasicInstance.shader", "res/textures/cat.png", count, modelMats, obj->va, obj->vb, obj->ib);
}

void InstancedGameObject::Draw() {
	if (isVisible) {
		material.Bind();
		va->Bind();
		ib->Bind();

		glm::mat4 view = parentScene->GetViewMat();
		glm::mat4 proj = parentScene->GetProjMat();
		glm::mat4 PV = proj * view;

		material.SetUniform("PV", PV);
		
		GLCALL(glDrawElementsInstanced(GL_TRIANGLES, ib->m_Count, GL_UNSIGNED_INT, nullptr, count));
	}
	
}
