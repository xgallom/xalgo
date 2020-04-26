//
// Created by xgallom on 4/24/20.
//

#include <xalgo/operations/EmptyOperations.h>
#include <xalgo/operations/OperationsStack.h>
#include <xalgo/workspace/Workspace.h>

namespace xalgo::EmptyOperations {
	bool constant(Workspace::Class *, Operations::Stack *stack, const double *constant) noexcept
	{
		stack->push(*constant);
		return true;
	}

	bool variable(Workspace::Class *workspace, Operations::Stack *stack, const VariableIdentifier *variable) noexcept
	{
		auto result = workspace->variables[variable->id];
		if(!result)
			result = workspace->variables[variable->name];
		if(!result)
			return false;

		stack->push(result);

		return true;
	}

	bool functionCall(Workspace::Class *, Operations::Stack *stack, const void *function) noexcept
	{
		// TODO: Implement
		return false;
	}
}
