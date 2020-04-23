//
// Created by xgallom on 4/23/20.
//

#include <xalgo/operations/Operations.h>
#include <stack>
#include <cstring>

namespace Operations {
	namespace {
	}

	void Operations::add(
			Function::Interface operationFunction,
			const uint8_t *parameter,
			size_t parameterSize,
			FunctionType::Enum functionType)
	{
		m_operationFunctions.push_back(operationFunction);
		m_parameters.insert(m_parameters.end(), parameter, parameter + parameterSize);
		m_parameterSizes.push_back(parameterSize);
		m_operationFunctionTypes.push_back(functionType);
	}

	double Operations::execute() const noexcept
	{
		auto operationFunction = m_operationFunctions.data();
		auto parameter = m_parameters.data();
		auto parameterSize = m_parameterSizes.data();
		auto functionType = m_operationFunctionTypes.begin();

		const auto end = operationFunction + size();
		std::stack<double, std::vector<double>> stack = {};

		for(; operationFunction < end; ++operationFunction, ++parameterSize) {
			switch(functionType++) {
				case FunctionType::Empty: {
					const auto operation = reinterpret_cast<Function::EmptyInterface>(*operationFunction);

					stack.push(operation());
					break;
				}

				case FunctionType::WithParameter: {
					const auto operation = reinterpret_cast<Function::WithParameterInterface>(*operationFunction);

					const auto parameterBegin = parameter;
					parameter += *parameterSize;

					stack.push(operation(parameterBegin));
					break;
				}

				case FunctionType::Unary: {
					const auto operation = reinterpret_cast<Function::UnaryInterface>(*operationFunction);

					const double x = stack.top();
					stack.pop();

					stack.push(operation(x));
					break;
				}

				case FunctionType::UnaryWithParameter: {
					const auto operation = reinterpret_cast<Function::UnaryWithParameterInterface>(*operationFunction);

					const double x = stack.top();
					stack.pop();

					const auto parameterBegin = parameter;
					parameter += *parameterSize;

					stack.push(operation(x, parameterBegin));
					break;
				}

				case FunctionType::Binary: {
					const auto operation = reinterpret_cast<Function::BinaryInterface>(*operationFunction);

					const double l = stack.top();
					stack.pop();

					const double r = stack.top();
					stack.pop();

					stack.push(operation(l, r));
					break;
				}

				case FunctionType::BinaryWithParameter: {
					const auto operation = reinterpret_cast<Function::BinaryWithParameterInterface>(*operationFunction);

					const double l = stack.top();
					stack.pop();

					const double r = stack.top();
					stack.pop();

					const auto parameterBegin = parameter;
					parameter += *parameterSize;

					stack.push(operation(l, r, parameterBegin));
					break;
				}

				case FunctionType::Count:
					break;
			}
		}

		return stack.top();
	}

	size_t Operations::size() const noexcept
	{
		return m_operationFunctions.size();
	}
}
