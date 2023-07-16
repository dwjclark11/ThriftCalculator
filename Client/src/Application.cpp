#include "Application.h"
#include <iostream>
#include <string>

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <SDL_opengl.h>
#include "../gen-cpp/calculator_constants.h"

namespace ThriftCalculator {
    std::unique_ptr<Application> Application::m_pInstance = nullptr;

    bool Application::Init()
    {
        // Init SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::string error = SDL_GetError();
            std::cout << "Failed to initialize SDL: " + error << std::endl;
            return false;
        }

        // Load the GL library
        if (SDL_GL_LoadLibrary(NULL) != 0)
        {
            std::string error = SDL_GetError();
            std::cout << "Failed to OpenGL library: " + error << std::endl;
            return false;
        }

        // Set the OpenGL attributes
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_pWindow = SDL_CreateWindow(
            "Thrift Calculator",        // Title
            SDL_WINDOWPOS_CENTERED,     // PosX
            SDL_WINDOWPOS_CENTERED,     // PosY
            m_WindowWidth,              // Window width
            m_WindowHeight,             // Window Height
            SDL_WINDOW_OPENGL           // Window flags
        );
        
        if (!m_pWindow)
        {
            std::string error = SDL_GetError();
            std::cout << "Failed to create SDL Window: " << error << std::endl;
            return false;
        }

        m_GLContext = SDL_GL_CreateContext(m_pWindow);

        if (!m_GLContext)
        {
            std::string error = SDL_GetError();
            std::cout << "Failed to initialize OpenGL context: " << error << std::endl;
            return false;
        }

        SDL_GL_MakeCurrent(m_pWindow, m_GLContext);
        SDL_GL_SetSwapInterval(1); 

        // Initialize Glad
        if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
        {
            std::cout << "Failed to LoadGL --> GLAD" << std::endl;
            return false;
        }

        m_pImGuiFunc = std::make_unique<ImGuiFunc>(m_pWindow, m_GLContext);

        if (!m_pImGuiFunc)
        {
            std::cout << "Failed to create the ImGuiFunc class!" << std::endl;
            return false;
        }

        return true;
    }

    void Application::ProcessEvents()
    {
        while (SDL_PollEvent(&m_Event))
        {
            ImGui_ImplSDL2_ProcessEvent(&m_Event);

            switch(m_Event.type)
            {
            case SDL_QUIT:
                m_bIsRunning = false;
                break;

            }
        }
    }

    void Application::Render()
    {
        glEnable(GL_BLEND);
        glViewport(0, 0, m_WindowWidth, m_WindowHeight);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: Add ImGui stuff here!
        m_pImGuiFunc->Begin();
        m_pImGuiFunc->Render();
        m_pImGuiFunc->End();
        SDL_GL_SwapWindow(m_pWindow);
    }

    void Application::CleanUp()
    {
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
    }
    
    Application::Application()
        : m_pWindow{nullptr}, m_GLContext{}, m_Event{}
        , m_pImGuiFunc{nullptr}, m_WindowWidth{ g_calculator_constants.WINDOW_WIDTH }, m_WindowHeight{ g_calculator_constants.WINDOW_HEIGHT }
        , m_bIsRunning{true}
    {

    }

    Application& Application::GetInstance()
    {
        if (!m_pInstance)
            m_pInstance.reset(new Application());

        return *m_pInstance;
    }

    Application::~Application()
    {
        std::cout << "Closing Application!" << std::endl;
    }

    void Application::Run()
    {
        if (!Init())
            m_bIsRunning = false;

        while (m_bIsRunning)
        {
            ProcessEvents();
            Render();
        }

        CleanUp();
    }
}