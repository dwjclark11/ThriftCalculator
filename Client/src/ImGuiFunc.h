#pragma once
#include <SDL.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <Calculator.h>
#include <calculator_constants.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace calculator;

namespace ThriftCalculator {
	class ImGuiFunc
	{
	private:
		const float BUTTON_SIZE_X = static_cast<float>(g_calculator_constants.BUTTON_SIZE_X);
		const float BUTTON_SIZE_Y = static_cast<float>(g_calculator_constants.BUTTON_SIZE_Y);

		SDL_Window* m_pWindow;
		SDL_GLContext m_GLContext;

		std::shared_ptr<TTransport> m_pSocket;
		std::shared_ptr<TTransport> m_pTransport;
		std::shared_ptr<TProtocol> m_pProtocol;

		std::unique_ptr<CalculatorClient> m_pClient;
		std::unique_ptr<Work> m_pWork;
		std::string m_sValueStr;

	private:

		/*
		* @brief Sets the values and the operation to be calculated.
		* @returns Returns true if the values are set successfully, false otherwise.
		*/
		bool SetValues(Operation::type op);

		/*
		* @brief Makes a call to the server to calculte the current
		* set numbers and operation.
		* @returns true if successful, false otherwise
		*/
		bool Calculate();

		/*
		* @brief Sets the colors and styles of the Imgui
		* buttons, window, etc
		*/
		void SetImguiStyle();
		
		/*
		* @brief This initializes ImGui backend for SDL and OpenGL.
		* @returns This Returns true if the initialization is successful, false otherwise.
		* @throws Throws TTransportException when trying to open the transport
		* if the Client is trying to be run while the
		* server is not running.
		*/
		bool Init();

	public:

		ImGuiFunc(SDL_Window* window, SDL_GLContext glContext);
		~ImGuiFunc();

		/*
		* @brief Render all the ImGui Widgets
		*/
		void Render();
		void Begin();
		void End();
	};
}