//
// Created by xgallom on 4/25/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_TYPEINFO_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_TYPEINFO_H

#include "TypeId.h"

namespace xalgo::core {
	template<typename T>
	struct GenericTypeInfo {
		using Type = T;
		static constexpr size_t Size = sizeof(Type);
	};

	template<typename T>
	struct TypeInfo {};

#define XALGO_CORE_CREATE_TYPE_INFO(TYPE, TYPE_ID) \
    template<> struct TypeInfo<TYPE> : GenericTypeInfo<TYPE> { \
        static constexpr size_t Id = TypeId::TYPE_ID; \
    }

	XALGO_CORE_CREATE_TYPE_INFO(void, Invalid);
	XALGO_CORE_CREATE_TYPE_INFO(int8_t, Int8);
	XALGO_CORE_CREATE_TYPE_INFO(uint8_t, UInt8);
	XALGO_CORE_CREATE_TYPE_INFO(int16_t, Int16);
	XALGO_CORE_CREATE_TYPE_INFO(uint16_t, UInt16);
	XALGO_CORE_CREATE_TYPE_INFO(int32_t, Int32);
	XALGO_CORE_CREATE_TYPE_INFO(uint32_t, UInt32);
	XALGO_CORE_CREATE_TYPE_INFO(int64_t, Int64);
	XALGO_CORE_CREATE_TYPE_INFO(uint64_t, UInt64);
	XALGO_CORE_CREATE_TYPE_INFO(float, Float);
	XALGO_CORE_CREATE_TYPE_INFO(double, Double);
	XALGO_CORE_CREATE_TYPE_INFO(long double, LongDouble);

#undef XALGO_CORE_CREATE_TYPE_INFO
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_TYPEINFO_H
