//
// Created by xgallom on 4/23/20.
//

#include <xalgo/operations/UnaryOperations.h>
#include <xalgo/operations/OperationsStack.h>
#include <xalgo/core/TypeInfo.h>

namespace xalgo::UnaryOperations {
	static bool invalidGenericImpl(Operations::Stack *, void *) noexcept
	{
		return false;
	}

	template<typename T>
	static bool minusGenericImpl(Operations::Stack *stack, void *valuePtr) noexcept
	{
		const auto value = reinterpret_cast<T *>(valuePtr);
		*value = -*value;
		return true;
	}

	template<typename T>
	static bool minusImpl(Operations::Stack *stack) noexcept
	{
		const auto result = stack->pop<T>();
		stack->push(-result());
		return bool(result);
	}

#define XALGO_CREATE_PRIMITIVE_OPERATION(TYPE_ID, TYPE) \
	bool minus##TYPE_ID(Operations::Stack *stack, const void *) { return minusImpl<TYPE>(stack); }

	XALGO_CREATE_PRIMITIVE_OPERATION(Int8, int8_t)
	XALGO_CREATE_PRIMITIVE_OPERATION(UInt8, uint8_t)
	XALGO_CREATE_PRIMITIVE_OPERATION(Int16, int16_t)
	XALGO_CREATE_PRIMITIVE_OPERATION(UInt16, uint16_t)
	XALGO_CREATE_PRIMITIVE_OPERATION(Int32, int32_t)
	XALGO_CREATE_PRIMITIVE_OPERATION(UInt32, uint32_t)
	XALGO_CREATE_PRIMITIVE_OPERATION(Int64, int64_t)
	XALGO_CREATE_PRIMITIVE_OPERATION(UInt64, uint64_t)
	XALGO_CREATE_PRIMITIVE_OPERATION(Float, float)
	XALGO_CREATE_PRIMITIVE_OPERATION(Double, double)
	XALGO_CREATE_PRIMITIVE_OPERATION(LongDouble, long double)

#undef XALGO_CREATE_PRIMITIVE_OPERATION

	__attribute__((weak)) bool minus(Operations::Stack *stack, const void *) noexcept
	{
		using CallInterface = bool (*)(Operations::Stack *, void *) noexcept;

		static constexpr CallInterface CallTable[XALGO_CONFIG_TYPE_ID_COUNT] = {
#define XALGO_CREATE_CALL_TABLE(TYPE) [core::TypeInfo<TYPE>::Id] = minusGenericImpl<TYPE>
#define XALGO_CREATE_DEFAULT_CALL_TABLE(TYPE) [core::TypeInfo<TYPE>::Id] = invalidGenericImpl

				XALGO_CREATE_DEFAULT_CALL_TABLE(void),
				XALGO_CREATE_CALL_TABLE(int8_t),
				XALGO_CREATE_DEFAULT_CALL_TABLE(uint8_t),
				XALGO_CREATE_DEFAULT_CALL_TABLE(int16_t),
				XALGO_CREATE_DEFAULT_CALL_TABLE(uint16_t),
				XALGO_CREATE_DEFAULT_CALL_TABLE(int32_t),
				XALGO_CREATE_DEFAULT_CALL_TABLE(uint32_t),
				XALGO_CREATE_DEFAULT_CALL_TABLE(int64_t),
				XALGO_CREATE_DEFAULT_CALL_TABLE(uint64_t),
				XALGO_CREATE_CALL_TABLE(float),
				XALGO_CREATE_CALL_TABLE(double),
				XALGO_CREATE_DEFAULT_CALL_TABLE(long double),

#undef XALGO_CREATE_DEFAULT_CALL_TABLE
#undef XALGO_CREATE_CALL_TABLE
		};

		const core::GenericType value = stack->top();

		if(!value)
			return false;
		else
			return CallTable[value.type](stack, value.value);
	}
}
