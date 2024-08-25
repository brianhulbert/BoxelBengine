#include "Scene.h"
#include "GameObject.h"
#include "GameWindow.h"

namespace scene {
	Scene::Scene(std::string name, GameWindow* w) : sceneName(name), parentWindow(w) {
		parentWindow->AddScene(this);
	}

	Transform& Scene::GetCameraTransform() { return parentWindow->currentScene->camera.GetTransform(); }

	glm::mat4 Scene::GetViewMat() { return camera.GetView(); }
	glm::mat4 Scene::GetProjMat() { return camera.GetProj(); }

	SceneMenu::SceneMenu(GameWindow* w) : Scene("Menu Scene", w) { }

	void SceneMenu::OnImGuiRender() {
		for (std::string s : m_Scenes) {
			if (ImGui::Button(s.c_str()))
				SetScene(s);
		}
	}

	void Scene::OnRender() {
		for (GameObject* entity : entities) {
			entity->Draw();
		}
	}

	void Scene::OnUpdate(float deltaTime) {
		for (GameObject* entity : entities) {
			entity->Update(deltaTime);
		}
	}

	void Scene::SetScene(std::string sceneName) {
		parentWindow->SetCurrentScene(sceneName);
	}

	void Scene::AddGameObject(GameObject* entity) {
		entities.push_back(entity);
	}
}