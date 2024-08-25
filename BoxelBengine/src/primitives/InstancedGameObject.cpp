#include "InstancedGameObject.h"

InstancedGameObject::InstancedGameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile, unsigned int count, Transform* transforms, VertexArray* va, VertexBuffer* vb, IndexBuffer* ib) :
	GameObject(parentScene, mesh, shaderfile, texturefile, va, vb, ib), count(count), transforms(transforms) {
	name = "Instanced Object";

	unsigned int transformBufferSize = count * sizeof(Transform);
	transformVB = new VertexBuffer(transforms, transformBufferSize);
	VertexBufferLayout transformBufferLayout;
	transformBufferLayout.Push<float>(3);
	transformBufferLayout.Push<float>(3);
	this->va->AddBuffer(*transformVB, transformBufferLayout);

}

InstancedGameObject* InstancedGameObject::CreateInstancedGameObject(scene::Scene* parentScene, Mesh* mesh, unsigned int count, Transform* transforms) {
	return new InstancedGameObject(parentScene, mesh, "res/shaders/BasicInstance.shader", "res/textures/cat.png", count, transforms);
}

InstancedGameObject* InstancedGameObject::CreateInstancedGameObject(GameObject* obj, unsigned int count, Transform* transforms) {
	obj->SetIndestructable();

	delete obj->shader;
	//delete obj->texture;

	return new InstancedGameObject(obj->parentScene, obj->mesh, "res/shaders/BasicInstance.shader", "res/textures/cat.png", count, transforms, obj->va, obj->vb, obj->ib);
}

void InstancedGameObject::Draw() {
	//TODO
}