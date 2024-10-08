#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "scenes/ClearColorScene.h"
#include "scenes/TextureScene.h"
#include "scenes/CubeScene.h"
#include "scenes/MotionScene.h"
#include "scenes/InstanceScene.h"
#include "GameWindow.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main(void)
{
    GameWindow game("Test app", true);
    std::cout << "c++ std: " << __cplusplus << std::endl;
    scene::SceneMenu* menuScene = new scene::SceneMenu(&game);
    scene::ClearColorScene* clearScene = new scene::ClearColorScene(&game);
    scene::TextureScene* textureScene = new scene::TextureScene(&game);
    scene::CubeScene* cubeScene = new scene::CubeScene(&game);
    scene::MotionScene* motionScene = new scene::MotionScene(&game);
    scene::InstanceScene* instanceScene = new scene::InstanceScene(&game);

    menuScene->AddScene(clearScene->GetName());
    menuScene->AddScene(textureScene->GetName());
    menuScene->AddScene(cubeScene->GetName());
    menuScene->AddScene(motionScene->GetName());
    menuScene->AddScene(instanceScene->GetName());

    game.SetCurrentScene(menuScene);

    game.Start();
    game.Stop();
    return 0;
}
