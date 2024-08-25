#pragma once
#include "scenes/Scene.h"
#include "GameObject.h"

//really a tetrahedron, but nobody knows that off the dome
class TriangleGameObject : public GameObject {
private:
	TriangleGameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile);
	~TriangleGameObject() {};
public:
	static TriangleGameObject* CreateTriangle(scene::Scene* scene, float scale = 1.0f);
};