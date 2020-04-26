//
// Created by xgallom on 4/23/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONS_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONS_H

#include "OperationFunction.h"
#include "../workspace/Workspace_fwd.h"

#include <vector>
#include <cstdint>

namespace xalgo::Operations {
	class Class {
		std::vector<Function::Interface> m_operationFunctions = {};
		std::vector<uint8_t> m_parameters = {};
		std::vector<size_t> m_parameterSizes = {};

	public:
		void add(Function::Interface operationFunction);
		void add(
				Function::Interface operationFunction,
				const uint8_t *parameter,
				size_t parameterSize
		);

		template<typename Parameter, typename std::enable_if_t<
				!std::is_same_v<Function::WithParameter<Parameter>, Function::Interface>, bool> = true>
		void add(
				Function::WithParameter<Parameter> operationFunction,
				const uint8_t *parameter,
				size_t parameterSize)
		{
			add(
					reinterpret_cast<Function::Interface>(operationFunction),
					parameter,
					parameterSize
			);
		}

		template<typename Parameter>
		void add(
				Function::WithParameter<Parameter> operationFunction,
				const Parameter &parameter)
		{
			add(
					reinterpret_cast<Function::Interface>(operationFunction),
					reinterpret_cast<const uint8_t *>(&parameter),
					sizeof(Parameter)
			);
		}

		bool execute(Workspace::Class *workspace, Stack *stack) const noexcept;

		void clear();

		[[nodiscard]] size_t size() const noexcept;

		[[nodiscard]] std::vector<Function::Interface> &operationFunctions() noexcept;
		[[nodiscard]] const std::vector<Function::Interface> &operationFunctions() const noexcept;
		[[nodiscard]] std::vector<uint8_t> &parameters() noexcept;
		[[nodiscard]] const std::vector<uint8_t> &parameters() const noexcept;
		[[nodiscard]] std::vector<size_t> &parameterSizes() noexcept;
		[[nodiscard]] const std::vector<size_t> &parameterSizes() const noexcept;


		[[nodiscard]] const Function::Interface &operationFunction(size_t index) const noexcept;
		template<typename T>
		[[nodiscard]] const T &parameter(size_t index) const noexcept
		{
			return *reinterpret_cast<const T *>(m_parameters.data() + index);
		}
		[[nodiscard]] const size_t &parameterSize(size_t index) const noexcept;
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONS_H
