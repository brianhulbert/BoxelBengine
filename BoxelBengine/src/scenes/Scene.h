#pragma once
#include <functional>
#include <iostream>
#include <string>

#include "Renderer.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "Camera.h"

class GameWindow;
class GameObject;

namespace scene {
	class Scene {
	//TODO: enable and disable blending
	public:
		//Set up everything needed for the scene
		Scene(std::string name, GameWindow* w);
		//Clean up everything from the scene
		virtual ~Scene() {}
		
		//Update uniforms, textures, etc..
		virtual void OnUpdate(float deltaTime);
		//Draw screen elements
		virtual void OnRender();
		//Render ImGui window
		virtual void OnImGuiRender (){}
		//Gets the name of the	 scene
		std::string GetName() { return sceneName; }
		void SetScene(std::string sceneName);
		glm::mat4 GetViewMat();
		glm::mat4 GetProjMat();
		Transform& GetCameraTransform();
		void AddGameObject(GameObject* entity);
	protected:
		std::string sceneName;
		GameWindow* parentWindow;
		Camera camera;
		std::vector<GameObject*> entities;
	};

	class SceneMenu : public Scene{
	public:
		SceneMenu(GameWindow* w);
		
		void AddScene(std::string name) {
			std::cout << "Adding scene: " << name << std::endl;
			m_Scenes.push_back(name);
		}
		void OnImGuiRender() override;
	private:
		std::vector<std::string> m_Scenes;
	};
}
