#pragma once

#include "Scene.h"
#include "Texture.h"
#include "GameObject.h"
#include <memory>

namespace scene {
	/*
	* This scene showcases the use of the translational and rotation 
	* velocity capabilities of the GameObject
	*/
	class MotionScene : public Scene {
	public:
		MotionScene(GameWindow* w);
		~MotionScene() {};

		void OnImGuiRender() override;
	private:
		GameWindow* gameWindow;
		Renderer renderer;
	};
}