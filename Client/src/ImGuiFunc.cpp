#include "ImGuiFunc.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <string>

namespace ThriftCalculator {

	bool ImGuiFunc::SetValues(Operation::type op)
	{
		if (m_sValueStr.empty())
			return false;

		if (m_pWork->bNumFirstNumSet && !m_pWork->bNumSecondNumSet)
		{
			m_pWork->op = op;
			m_sValueStr = "0";
		}
		else
		{
			int32_t num = atoi(m_sValueStr.c_str());
			m_pWork->op = op;
			m_pWork->num1 = num;
			m_pWork->bNumFirstNumSet = true;
			m_sValueStr = "0";
		}
		
		return true;
	}

	bool ImGuiFunc::Calculate()
	{
		// Do not do anything if there are no numbers set
		if (m_sValueStr.empty() || !m_pWork->bNumFirstNumSet)
			return false;

		if (m_pWork->bNumFirstNumSet && !m_pWork->bNumSecondNumSet)
		{
			int32_t num = atoi(m_sValueStr.c_str());
			m_pWork->num2 = num;
			m_pWork->bNumSecondNumSet = true;
		}
		
		// If both numbers have been set, we can now send the work to the
		// server to be calculated
		if (m_pWork->bNumFirstNumSet && m_pWork->bNumSecondNumSet)
		{
			auto value = m_pClient->calculate(*m_pWork);
			m_sValueStr = std::to_string(value);

			// The new first num is now equal to the result
			m_pWork->bNumSecondNumSet = false;
			m_pWork->num1 = value;
		}

		return true;
	}

	void ImGuiFunc::SetImguiStyle()
    {
		ImGuiStyle& style = ImGui::GetStyle();
		style.TabRounding = 0.0f;
		style.FrameBorderSize = 1.0f;
		style.ScrollbarRounding = 0.0f;
		style.ScrollbarSize = 5.0f;
		style.WindowPadding = ImVec2{ 3.f, 3.f };
		style.ItemSpacing = ImVec2{ 4.f, 1.f };
		style.FramePadding = ImVec2{ 2.f, 1.f };

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); //  - white
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); // Greyish
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);  // Black Transparent
		colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.22f, 0.50f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.27f, 0.75f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.33f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.311f, 0.492f, 0.597f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.35f, 0.35f, 0.37f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);

		style.WindowMenuButtonPosition = ImGuiDir_Right;
    }

    bool ImGuiFunc::Init()
    {
		const char* glsl_version = "#version 450";
		IMGUI_CHECKVERSION();

		if (!ImGui::CreateContext())
		{
			std::cout << "Failed to create imgui context!" << std::endl;
			return false;
		}

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		// Only want the windows to be moved by the titlebar
		io.ConfigWindowsMoveFromTitleBarOnly = true;

		// Setup Platform/Renderer backends
		if (!ImGui_ImplSDL2_InitForOpenGL(
			m_pWindow,
			m_GLContext
		))
		{
			std::cout << "Failed to initialize ImGui_SDL2_For_OpenGL!" << std::endl;
			return false;
		}

		if (!ImGui_ImplOpenGL3_Init(glsl_version))
		{
            std::cout << "Failed to initialize ImGui_OpenGL3!" << std::endl;
			return false;
		}

		// Setup ImGui Style
		SetImguiStyle();

		if (m_pSocket = std::make_shared<TSocket>("localhost", 9090); !m_pSocket)
		{
			std::cout << "Failed to create the TSocket!" << std::endl;
			return false;
		}
			
		if (m_pTransport = std::make_shared<TBufferedTransport>(m_pSocket); !m_pTransport)
		{
			std::cout << "Failed to create the TBufferedTransport!" << std::endl;
			return false;
		}

		if (m_pProtocol = std::make_shared<TBinaryProtocol>(m_pTransport); !m_pProtocol)
		{
			std::cout << "Failed to create the TBinaryProtocol!" << std::endl;
			return false;
		}

		if (m_pClient = std::make_unique<CalculatorClient>(m_pProtocol); !m_pClient)
		{
			std::cout << "Failed to create the CalculatorClient!" << std::endl;
			return false;
		}

		if (m_pWork = std::make_unique<Work>(); !m_pWork)
		{
			std::cout << "Failed to create the Work ptr" << std::endl;
			return false;
		}
		
		try
		{
			m_pTransport->open();
		}
		catch (TTransportException& ex)
		{
			assert(false && "Did you forget to start the server?");
			std::cout << "Failed to create ImGui Functions - Transport Exception: " << ex.what() << std::endl;
			return false;
		}
		
		return true;
    }

    ImGuiFunc::ImGuiFunc(SDL_Window* window, SDL_GLContext glContext)
        : m_pWindow(window), m_GLContext(glContext)
		, m_pSocket{ nullptr }, m_pTransport{ nullptr }, m_pProtocol{ nullptr }
		, m_pClient{ nullptr }, m_pWork{nullptr}, m_sValueStr{"0"}
    {
        if (!Init())
        {
            throw std::runtime_error("Failed to Initialize ImGuiFuncs!");
        }
    }

	ImGuiFunc::~ImGuiFunc()
	{
		if (m_pTransport)
			m_pTransport->close();
	}

    void ImGuiFunc::Render()
    {
        auto io = ImGui::GetIO();

        io.DisplaySize.x = static_cast<float>(g_calculator_constants.WINDOW_WIDTH);
        io.DisplaySize.y = static_cast<float>(g_calculator_constants.WINDOW_HEIGHT);
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::SetNextWindowPos(ImVec2{ 0, 0 });

        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoMove;
        flags |= ImGuiWindowFlags_NoTitleBar;
        flags |= ImGuiWindowFlags_NoResize;
        flags |= ImGuiWindowFlags_NoCollapse;
        flags |= ImGuiWindowFlags_NoDecoration;

        if (!ImGui::Begin("Calculator", 0, flags))
        {
            ImGui::End();
            return;
        }

		ImGui::NewLine();

		// Center the text
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(m_sValueStr.c_str()).x;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		ImGui::Text(m_sValueStr.c_str());
		
		ImGui::SetCursorPosY(32.f);
		ImGui::Separator();
		ImGui::NewLine();

		ImGuiTableFlags tableFlags = 0;
		tableFlags |= ImGuiTableFlags_SizingFixedFit;

		ImGui::SetCursorPosX(80.f);
		if (ImGui::BeginTable("Numbers", 3, tableFlags))
		{
			for (int i = 0; i < 3; i++)
			{
				ImGui::TableNextRow();
				for (int j = 0; j < 3; j++)
				{
					ImGui::TableSetColumnIndex(j);
					int buttonNum = (7 - 3 * i) + j;
					std::string buttonStr = std::to_string(buttonNum);
					if (ImGui::Button(buttonStr.c_str(), ImVec2{BUTTON_SIZE_X, BUTTON_SIZE_Y}))
					{
						if (m_sValueStr == "0")
							m_sValueStr = buttonStr;
						else
							m_sValueStr += buttonStr;
					}
				}
			}

			ImGui::EndTable();
		}
		
		ImGui::SetCursorPosX(80.f);
		if (ImGui::Button(" 0 ", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
		{
			if (!m_sValueStr.empty() && m_sValueStr != "0")
			{
				m_sValueStr += "0";
			}
		}

		ImGui::SameLine(0, 8.f);
		if (ImGui::Button("+/-", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
		{
			if (!m_sValueStr.empty() && m_sValueStr != "0")
			{
				if (m_sValueStr.at(0) == '-')
					m_sValueStr.erase(0, 1);
				else
					m_sValueStr.insert(0, "-");
			}
		}

		ImGui::SameLine(0, 8.f);

		if (ImGui::Button("DEL", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
		{
			// Pop off the last letter
			if (!m_sValueStr.empty())
				m_sValueStr.pop_back();

			// Check to see if the last letter is a negative and remove it
			if (m_sValueStr == "-")
				m_sValueStr.pop_back();
		}

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		ImGui::SetCursorPosX(40.f);
		if (ImGui::Button(" + ", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
			SetValues(Operation::ADD);

		ImGui::SameLine(0, 16.f);
		
		if (ImGui::Button(" - ", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
			SetValues(Operation::SUBTRACT);

		ImGui::SameLine(0, 16.f);

		if (ImGui::Button(" / ", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
			SetValues(Operation::DIVIDE);

		ImGui::SameLine(0, 16.f);
		if (ImGui::Button(" * ", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
			SetValues(Operation::MULTIPLY);

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
		
		ImGui::SetCursorPosX(106.f);

		if (ImGui::Button(" = ", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
		{
			try
			{
				Calculate();
			}
			catch (InvalidOperation&)
			{
				m_pWork.reset(new Work());
				m_sValueStr = "0";
			}
		}
		ImGui::SameLine(0.f, 16.f);
		if (ImGui::Button(" CE ", ImVec2{ BUTTON_SIZE_X, BUTTON_SIZE_Y }))
		{
			m_pWork.reset(new Work());
			m_sValueStr = "0";
		}

        ImGui::End();
    }

    void ImGuiFunc::Begin()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiFunc::End()
    {
        // Rendering
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(
                m_pWindow,
                backup_current_context);
        }
    }

}
