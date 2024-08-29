#pragma once

#include "Scene.h"
#include "Texture.h"
#include "GameObject.h"
#include <memory>

namespace scene {
	/*
	* This scene showcases the use of an instance object. Instanced objects are great
	* for drawing the same mesh in many locations with a singular draw call. (This is a
	* lot faster than a bunch of individual draw calls because there is a lot of overhead
	* with a draw call or something like that). Good for grass, bushes, trees, etc...
	*/
	class InstanceScene : public Scene {
	public:
		InstanceScene(GameWindow* w);
		~InstanceScene() {};

		void OnImGuiRender() override;
	private:
		GameWindow* gameWindow;
		Renderer renderer;
	};
}
