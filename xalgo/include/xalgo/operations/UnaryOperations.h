//
// Created by xgallom on 4/23/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_UNARYOPERATIONS_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_UNARYOPERATIONS_H

#include "SystemOperations.h"
#include "OperationFunction.h"

namespace xalgo::UnaryOperations
{
	bool minusInt8(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusUInt8(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusInt16(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusUInt16(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusInt32(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusUInt32(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusInt64(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusUInt64(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusFloat(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusDouble(Workspace::Class *workspace, Operations::Stack *stack, const void *);
	bool minusLongDouble(Workspace::Class *workspace, Operations::Stack *stack, const void *);

	inline constexpr Operations::Function::Interface minusPrimitive[core::TypeId::Count] = {
			[core::TypeId::Invalid] = SystemOperations::invalid,

			[core::TypeId::Int8] = minusInt8,
			[core::TypeId::UInt8] = minusUInt8,
			[core::TypeId::Int16] = minusInt16,
			[core::TypeId::UInt16] = minusUInt16,
			[core::TypeId::Int32] = minusInt32,
			[core::TypeId::UInt32] = minusUInt32,
			[core::TypeId::Int64] = minusInt64,
			[core::TypeId::UInt64] = minusUInt64,
			[core::TypeId::Float] = minusFloat,
			[core::TypeId::Double] = minusDouble,
			[core::TypeId::LongDouble] = minusLongDouble,
	};

	bool minus(Workspace::Class *workspace, Operations::Stack *stack, const void *) noexcept;
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_UNARYOPERATIONS_H
