#include "InstanceScene.h"
#include "primitives/CubeGameObject.h"
#include "primitives/InstancedGameObject.h"

namespace scene{
	InstanceScene::InstanceScene(GameWindow* w) : Scene("Instance Scene", w) {
		int numCubes = 20;
		Transform* cubeTransforms = (Transform*)malloc(numCubes * sizeof(Transform));
		for (int i = 0; i < numCubes; i++) {
			cubeTransforms[i].translation = glm::vec3(2.0f * (float)i, 0.0f, 0.0f);
		}

		GameObject* cube = CubeGameObject::CreateCube(this);
		GameObject* InstancedCube = InstancedGameObject::CreateInstancedGameObject(cube, numCubes, cubeTransforms);

		AddGameObject(InstancedCube);

		delete cube;
	}
}