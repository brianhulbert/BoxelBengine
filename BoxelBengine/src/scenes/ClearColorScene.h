#pragma once

#include "Scene.h"

namespace scene {
	class ClearColorScene : public Scene {
	public:
		ClearColorScene(GameWindow* w);
		~ClearColorScene();


		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}