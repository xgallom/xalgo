//
// Created by xgallom on 4/24/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_EMPTYOPERATIONS_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_EMPTYOPERATIONS_H

#include "OperationsStack_fwd.h"
#include "../workspace/Workspace_fwd.h"

#include <cstddef>

namespace xalgo::EmptyOperations {
	struct VariableIdentifier {
		size_t id;
		char name[1]; // Name is variable sized
	};

	bool constant(Workspace::Class *workspace, Operations::Stack *stack, const double *constant) noexcept;
	bool variable(Workspace::Class *workspace, Operations::Stack *stack, const VariableIdentifier *variable) noexcept;
	bool functionCall(Workspace::Class *workspace, Operations::Stack *stack, const void *function) noexcept;
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_EMPTYOPERATIONS_H
