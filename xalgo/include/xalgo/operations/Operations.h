//
// Created by xgallom on 4/23/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONS_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONS_H

#include "OperationFunction.h"

namespace Operations {
	class Operations {
		std::vector<Function::Interface> m_operationFunctions = {};
		std::vector<uint8_t> m_parameters = {};
		std::vector<size_t> m_parameterSizes = {};
		FunctionTypes m_operationFunctionTypes = {};

	public:
		void add(
				Function::Interface operationFunction,
				const uint8_t *parameter,
				size_t parameterSize,
				FunctionType::Enum functionType
		);

		[[nodiscard]] double execute() const noexcept;

		[[nodiscard]] size_t size() const noexcept;
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONS_H
