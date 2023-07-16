#include "CalculatorHandler.h"

namespace ThriftCalculator {

	int32_t CalculatorHandler::calculate(const Work& work)
	{
		std::cout << "calculate(" << work << ")" << std::endl;
		int32_t val;

		switch (work.op)
		{
		case Operation::ADD:
			val = work.num1 + work.num2;
			break;
		case Operation::SUBTRACT:
			val = work.num1 - work.num2;
			break;
		case Operation::MULTIPLY:
			val = work.num1 * work.num2;
			break;
		case Operation::DIVIDE:
			if (work.num2 == 0)
			{
				InvalidOperation io;
				io.op = work.op;
				io.why = "cannot divide by 0";
				throw io;
			}
			val = work.num1 / work.num2;
			break;
		default:
			InvalidOperation io;
			io.op = work.op;
			io.why = "Invalid Operation";
			throw io;
		}

		std::cout << "Calculated Value for " << work.num1 << " " << work.op << " " << work.num2 << " = " << val << std::endl;
		return val;
	}

	CalculatorIf* CalculatorCloneFactory::getHandler(const ::apache::thrift::TConnectionInfo& connInfo)
	{
		std::shared_ptr<TSocket> socket = std::dynamic_pointer_cast<TSocket>(connInfo.transport);
		std::cout << "Incoming connection\n";
		std::cout << "SocketInfo: " << socket->getSocketInfo() << "\n";
		//std::cout << "PeerHost: " << socket->getPeerHost() << "\n";
		std::cout << "PeerAddress: " << socket->getPeerAddress() << "\n";
		std::cout << "PeerPort: " << socket->getPeerPort() << "\n";
		return new CalculatorHandler;
	}

	void CalculatorCloneFactory::releaseHandler(CalculatorIf* handler)
	{
		if (handler)
		{
			delete handler;
			handler = nullptr;
		}
	}

}