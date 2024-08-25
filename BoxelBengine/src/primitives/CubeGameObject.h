#pragma once
#include "scenes/Scene.h"
#include "GameObject.h"

class CubeGameObject : public GameObject {
private:
	CubeGameObject(scene::Scene* parentScene, Mesh* mesh, std::string shaderfile, std::string texturefile);
public:
	static CubeGameObject* CreateCube(scene::Scene* scene, float scale = 1.0f);
};