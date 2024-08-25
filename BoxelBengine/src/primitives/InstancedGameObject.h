#pragma once

#include "scenes/Scene.h"
#include "GameObject.h"

class InstancedGameObject : public GameObject {
public:
	static InstancedGameObject* CreateInstancedGameObject(scene::Scene* scene, Mesh* mesh, unsigned int count, Transform* transforms);
	static InstancedGameObject* CreateInstancedGameObject(GameObject* obj, unsigned int count, Transform* transforms);

	void Draw() override;
private:
	InstancedGameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile, unsigned int count, Transform* transforms, VertexArray* va = nullptr, VertexBuffer* vb = nullptr, IndexBuffer* ib = nullptr);
	unsigned int count;
	Transform* transforms;
	VertexBuffer* transformVB;
};