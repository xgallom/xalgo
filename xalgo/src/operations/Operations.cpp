//
// Created by xgallom on 4/23/20.
//

#include <xalgo/operations/Operations.h>

namespace xalgo::Operations {
	void Class::add(Function::Interface operationFunction)
	{
		m_operationFunctions.push_back(operationFunction);
		m_parameterSizes.push_back(0);
	}

	void Class::add(
			Function::Interface operationFunction,
			const uint8_t *parameter,
			size_t parameterSize)
	{
		m_operationFunctions.push_back(operationFunction);
		m_parameters.insert(m_parameters.end(), parameter, parameter + parameterSize);
		m_parameterSizes.push_back(parameterSize);
	}

	bool Class::execute(Stack *stack) const noexcept
	{
		auto operationFunction = m_operationFunctions.data();
		auto parameter = m_parameters.data();
		auto parameterSize = m_parameterSizes.data();

		const auto end = operationFunction + size();

		while(operationFunction < end) {
			if(!(**operationFunction++)(stack, parameter))
				return false;
		}

		return true;
	}

	void Class::clear()
	{
		m_operationFunctions.clear();
		m_parameters.clear();
		m_parameterSizes.clear();
	}

	size_t Class::size() const noexcept
	{
		return m_operationFunctions.size();
	}

	const std::vector<Function::Interface> &Class::operationFunctions() const noexcept
	{
		return m_operationFunctions;
	}

	const std::vector<uint8_t> &Class::parameters() const noexcept
	{
		return m_parameters;
	}

	const std::vector<size_t> &Class::parameterSizes() const noexcept
	{
		return m_parameterSizes;
	}

	const Function::Interface &Class::operationFunction(size_t index) const noexcept
	{
		return m_operationFunctions[index];
	}

	const size_t &Class::parameterSize(size_t index) const noexcept
	{
		return m_parameterSizes[index];
	}
}
