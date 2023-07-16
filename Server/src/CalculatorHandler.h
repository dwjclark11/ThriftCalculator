#pragma once
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include <Calculator.h>

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace calculator;

namespace ThriftCalculator {
	class CalculatorHandler : public CalculatorIf
	{

	public:
		CalculatorHandler() = default;
		int32_t calculate(const Work& work) override;
	};

	class CalculatorCloneFactory : virtual public CalculatorIfFactory
	{
	public:
		~CalculatorCloneFactory() override = default;
		CalculatorIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) override;

		void releaseHandler(CalculatorIf* handler) override;
	};
}