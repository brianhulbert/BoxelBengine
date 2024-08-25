#include "ClearColorScene.h"

namespace scene {
	ClearColorScene::ClearColorScene(GameWindow* w) : m_ClearColor {1.0f, 1.0f, 1.0f, 1.0f}, Scene("Clear Color", w) {

	}

	ClearColorScene::~ClearColorScene(){}

	void ClearColorScene::OnUpdate(float deltaTime) {}

	void ClearColorScene::OnRender() {
		GLCALL(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	void ClearColorScene::OnImGuiRender() {
		if (ImGui::Button("<-")) {
			SetScene("Menu Scene");
		}
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}