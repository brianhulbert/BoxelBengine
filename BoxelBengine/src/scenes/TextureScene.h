#pragma once

#include "Scene.h"
#include "Texture.h"
#include "GameObject.h"
#include <memory>

namespace scene {
	class TextureScene : public Scene {
	public:
		TextureScene(GameWindow* w);
		~TextureScene();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		Renderer renderer;
		std::unique_ptr<VertexArray> m_VA;
		std::unique_ptr<VertexBuffer> m_VB;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Shader> m_Shader;
		glm::vec3 m_TextureTranslation;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
	};
}