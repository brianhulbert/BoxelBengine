#include "TextureScene.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace scene {
	TextureScene::TextureScene(GameWindow* w) : Scene("Texture Scene", w), m_TextureTranslation(0.0f, 0.0f, 0.0f),
		m_Proj(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)), m_View(glm::mat4(1.0f)) {
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,  //0
			 0.5f, -0.5f, 1.0f, 0.0f,  //1
			 0.5f,  0.5f, 1.0f, 1.0f,  //2
			-0.5f,  0.5f, 0.0f, 1.0f   //3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		
		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//OpenGL buffers required
		m_VA = std::make_unique<VertexArray>();
		m_VB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VA->AddBuffer(*m_VB, layout);
		 
		m_IB = std::make_unique<IndexBuffer>(indices, 6);
		m_IB->Bind();

		//Create shader
		m_Shader = std::make_unique<Shader>("res/shaders/Basic2D.shader");
		m_Shader->Bind();

		//Texture Creation
		m_Texture = std::make_unique<Texture>("res/textures/cat.png");
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TextureScene::~TextureScene(){}

	void TextureScene::OnUpdate(float deltaTime) {}

	void TextureScene::OnRender() {
		Renderer renderer;

		m_Texture->Bind();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TextureTranslation);
		glm::mat4  MVP = m_Proj * m_View * model;

		m_Shader->SetUniformMat4f("u_MVP", MVP);

		renderer.Draw(*m_VA, *m_IB, *m_Shader);
	}

	void TextureScene::OnImGuiRender() {
		if (ImGui::Button("<-")) {
			SetScene("Menu Scene");
			return;
		}
		ImGui::SliderFloat3("Texture Translation", &m_TextureTranslation.x, -1.0f, 1.0f);
	}
}