#include "GameWindow.h"
#include "scenes/Scene.h"

GameWindow::GameWindow(std::string name, bool enable_vsync, bool enable_blending, bool enable_debug) : 
    windowName(name), windowStatus(UNKNOWN), renderer(), debug(enable_debug), scenes(), currentScene(nullptr)  {
    /* Initialize the library */
    if (!glfwInit()) {
        windowStatus = ERROR;
        std::cout << "Setup Error" << std::endl;
        return;
    }

    /* Get main monitor dimensions */
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    int monitor_width;
    int monitor_height;
    glfwGetMonitorWorkarea(monitor, NULL, NULL, &monitor_width, &monitor_height);

    /* Create a windowed mode window and its OpenGL context */
    //window = glfwCreateWindow(monitor_width, monitor_height, "Hello World", monitor, NULL); // for full screen
    window = glfwCreateWindow(monitor_width, monitor_height, windowName.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        windowStatus = ERROR;
        std::cout << "Setup Error" << std::endl;
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if(enable_vsync)
        glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) {
        if (debug)
            std::cout << "GLEW Error!" << std::endl;
        windowStatus = ERROR;
        std::cout << "Setup Error" << std::endl;
        return;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    if (enable_blending){
        // Enable depth testing
        GLCALL(glEnable(GL_DEPTH_TEST));
        glDepthFunc(GL_LESS); // Default depth function

        // Enable blending
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }
    
    if (debug) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls    
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }
    windowStatus = READY;
}

GameWindow::~GameWindow() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void GameWindow::Start() {
    /*if (windowStatus == READY) {
        windowStatus = RUNNING;
        renderThread = std::make_unique<std::thread>([this]() {
            this->Run();
            });
    }*/
    windowStatus = RUNNING;
    Run();
}

void GameWindow::Run() {
    std::cout << "Starting render thread" << std::endl;
    glfwMakeContextCurrent(window);

    ImGuiIO& io = ImGui::GetIO();
    double previousTime = glfwGetTime();
    while (!glfwWindowShouldClose(window) && windowStatus == RUNNING)
    {
        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();
        
        //will eventually create a separate thread for this
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - previousTime;
        previousTime = currentTime;
        currentScene->OnUpdate((float)deltaTime);

        //Render the scene
        currentScene->OnRender();

        if (debug) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if (currentScene) {
                ImGui::Begin("Scene settings");
                currentScene->OnUpdate(0.0f);
                currentScene->OnImGuiRender();
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    std::cout << "Ending render thread" << std::endl;
    windowStatus = STOPPED;
}

void GameWindow::Stop() {
    //Will wait for the current rendering thread to stop, and clean up all the scenes
    windowStatus = STOPPED;
    if (renderThread)
        renderThread->join();
    for (auto s : scenes)
        delete s.second;
}

void GameWindow::AddScene(scene::Scene* s) {
    scenes[s->GetName()] = s;
}

void GameWindow::SetCurrentScene(std::string sceneName) {
    currentScene = scenes[sceneName];
}

void GameWindow::SetCurrentScene(scene::Scene* scene) {
    currentScene = scene;
    std::cout << "Setting scene to " << scene->GetName() << std::endl;
}

GameWindowStatus GameWindow::GetWindowStatus() { return windowStatus; }

scene::Scene* GameWindow::GetScene(std::string sceneName) {
    return scenes[sceneName];
}