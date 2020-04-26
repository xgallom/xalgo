//
// Created by xgallom on 4/23/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONFUNCTION_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONFUNCTION_H

#include "OperationsStack.h"

namespace xalgo::Operations::Function {
	template<typename Parameter>
	using WithParameter = bool (Stack *stack, const Parameter *parameter);
	using Interface = bool (*)(Stack *stack, const void *parameter);
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONFUNCTION_H
