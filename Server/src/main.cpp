#include "CalculatorHandler.h"

int main()
{
	std::cout << "Starting Server..." << std::endl;
	TThreadedServer server(
		std::make_shared<CalculatorProcessorFactory>(std::make_shared<ThriftCalculator::CalculatorCloneFactory>()),
		std::make_shared<TServerSocket>(9090), //port
		std::make_shared<TBufferedTransportFactory>(),
		std::make_shared<TBinaryProtocolFactory>());

	server.serve();
	return 0;
}