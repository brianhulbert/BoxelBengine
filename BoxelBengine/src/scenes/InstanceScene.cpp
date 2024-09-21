#include "InstanceScene.h"
#include "primitives/CubeGameObject.h"
#include "primitives/InstancedGameObject.h"

namespace scene{
	InstanceScene::InstanceScene(GameWindow* w) : Scene("Instance Scene", w) {
		int rows = 50;
		int cols = 70;
		float step = 2.0f;
		int numCubes = rows * cols;
		Transform* cubeTransforms = (Transform*)malloc(numCubes * sizeof(Transform));
		int index = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cubeTransforms[index].translation = glm::vec3((j * step) - cols, (i * step) - rows, 0.0f);
				index++;
			}
		}

		GameObject* cube = CubeGameObject::CreateCube(this);
		GameObject* InstancedCube = InstancedGameObject::CreateInstancedGameObject(cube, numCubes, cubeTransforms);

		AddGameObject(InstancedCube);

		camera.SetProj(glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 200.0f));
		camera.transform.translation = glm::vec3(0.0f, 0.0f, 7.0f);

		delete cube;
	}

	void InstanceScene::OnImGuiRender() {
		if (ImGui::Button("<-")) {
			SetScene("Menu Scene");
		}
		ImGui::Text(entities[0]->name.c_str());
		ImGui::SliderFloat3("Translation", &entities[0]->transform.translation.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Rotation", &entities[0]->transform.rotation.x, -360.0f, 360.0f);
		ImGui::SliderFloat3("Camera Translation", &GetCameraTransform().translation.x, 0.0f, 100.0f);
		ImGui::SliderFloat3("Camera Rotation", &GetCameraTransform().rotation.x, -360.0f, 360.0f);
	}
}