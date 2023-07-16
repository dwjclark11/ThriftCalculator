#pragma once
#include <SDL.h>
#include <memory>
#include "ImGuiFunc.h"

namespace ThriftCalculator {
	class Application
	{
	private:
		SDL_Window* m_pWindow;
		SDL_GLContext m_GLContext;
		SDL_Event m_Event;
		std::unique_ptr<ImGuiFunc> m_pImGuiFunc;
		int m_WindowWidth, m_WindowHeight;
		bool m_bIsRunning;

	private:
		bool Init();
		void ProcessEvents();
		void Render();
		void CleanUp();

		Application();
		static std::unique_ptr<Application> m_pInstance;
	public:
		static Application& GetInstance();
		~Application();

		void Run();
	};
}