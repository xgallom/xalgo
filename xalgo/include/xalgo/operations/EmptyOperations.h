//
// Created by xgallom on 4/24/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_EMPTYOPERATIONS_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_EMPTYOPERATIONS_H

#include "OperationsStack_fwd.h"

namespace xalgo::EmptyOperations {
	bool constant(Operations::Stack *stack, const double *constant) noexcept;
	bool variable(Operations::Stack *stack, const char *variable) noexcept;
	bool functionCall(Operations::Stack *stack, const void *function) noexcept;
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_EMPTYOPERATIONS_H
