//
// Created by xgallom on 4/24/20.
//

#include <xalgo/operations/EmptyOperations.h>
#include <xalgo/operations/OperationsStack.h>

namespace xalgo::EmptyOperations {
	bool constant(Operations::Stack *stack, const double *constant) noexcept
	{
		stack->push(*constant);
		return true;
	}

	bool variable(Operations::Stack *stack, const char *variable) noexcept
	{
		// TODO: Implement
		return false;
	}

	bool functionCall(Operations::Stack *stack, const void *function) noexcept
	{
		// TODO: Implement
		return false;
	}
}
