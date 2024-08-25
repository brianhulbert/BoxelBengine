#pragma once

#include "Scene.h"
#include "Texture.h"
#include "GameObject.h"
#include <memory>

namespace scene {
	/* 
	* This scene showcases the use of a primative GameObject
	*/
	class CubeScene : public Scene {
	public:
		CubeScene(GameWindow* w);
		~CubeScene() {};

		void OnImGuiRender() override;
	private:
		GameWindow* gameWindow;
		Renderer renderer;
		GameObject* cube;
	};
}
