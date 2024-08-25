#include "CubeScene.h"
#include "primitives/CubeGameObject.h"

namespace scene {
	CubeScene::CubeScene(GameWindow* g) : Scene("Cube Scene", g), gameWindow(g) {
		cube = CubeGameObject::CreateCube(this);
		camera.SetProj(glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f));
		AddGameObject(cube);
	}

	void CubeScene::OnImGuiRender() {
		if (ImGui::Button("<-")) {
			SetScene("Menu Scene");
		}
		ImGui::SliderFloat3("Cube Translation", &cube->transform.translation.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Cube Rotation", &cube->transform.rotation.x, -360.0f, 360.0f);
		ImGui::SliderFloat3("Camera Translation", &GetCameraTransform().translation.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Camera Rotation", &GetCameraTransform().rotation.x, -360.0f, 360.0f);
	}
}