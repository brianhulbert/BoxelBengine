#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <memory>
#include <thread>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "imGUI/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

enum GameWindowStatus {
	READY,
	RUNNING,
	STOPPED,
	ERROR,
	UNKNOWN
};

namespace scene {
	class Scene;
}

class GameWindow {
public:
	GameWindow(std::string name, bool enable_vsync = true, bool enable_blending = true, bool enable_debug = true);
	~GameWindow();

	GameWindowStatus GetWindowStatus();
	void SetCurrentScene(std::string sceneName);
	void SetCurrentScene(scene::Scene* s);
	void AddScene(scene::Scene* s);
	scene::Scene* GetScene(std::string name);
	void Start();
	void Stop();
	scene::Scene* currentScene;
private:
	void Run();
	std::unique_ptr<std::thread> renderThread;
	std::string windowName;
	GameWindowStatus windowStatus;
	Renderer renderer;
	bool debug;
	std::unordered_map<std::string, scene::Scene*> scenes;
	GLFWwindow* window;
};