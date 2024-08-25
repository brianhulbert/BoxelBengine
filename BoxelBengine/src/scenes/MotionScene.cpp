#include "MotionScene.h"
#include "primitives/CubeGameObject.h"
#include "primitives/TriangleGameObject.h"

namespace scene {
	MotionScene::MotionScene(GameWindow* g) : Scene("Motion Scene", g), gameWindow(g) {
		int max = 3;
		for (int i = 0; i < max; i++) {
			for (int j = 0; j < max; j++) {
				CubeGameObject* cube = CubeGameObject::CreateCube(this);
				cube->velocity.rotVelocity.x = (360.0f / max) * i;
				cube->velocity.rotVelocity.y = (360.0f / max) * j;

				cube->transform.translation = glm::vec3( (i * 2) - max, (j * 2)- max, -10.0);

				AddGameObject(cube);
			}
		}

		camera.SetProj(glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f));
		camera.transform.translation = glm::vec3(0.0f, 0.0f, 7.0f);
	}

	void MotionScene::OnImGuiRender() {
		if (ImGui::Button("<-")) {
			SetScene("Menu Scene");
		}
		ImGui::Text(entities[0]->name.c_str());
		ImGui::SliderFloat3("Translation", & entities[0]->transform.translation.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Rotation", &entities[0]->transform.rotation.x, -360.0f, 360.0f);
		ImGui::SliderFloat3("Translation velocity (units/s)", &entities[0]->velocity.transVelocity.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Rotation velocity (degrees/s)", &entities[0]->velocity.rotVelocity.x, -360.0f, 360.0f);
		ImGui::SliderFloat3("Camera Translation", &GetCameraTransform().translation.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Camera Rotation", &GetCameraTransform().rotation.x, -360.0f, 360.0f);
	}
}