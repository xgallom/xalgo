//
// Created by xgallom on 4/26/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_TYPEID_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_TYPEID_H

#include <cstddef>

namespace xalgo::core::TypeId {
	enum Enum : size_t {
		Invalid = 0,

		Int8,
		UInt8,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Float,
		Double,
		LongDouble,

		Count
	};
}

#ifndef XALGO_CONFIG_TYPE_ID_COUNT
#define XALGO_CONFIG_TYPE_ID_COUNT ::xalgo::core::TypeId::Count
#endif

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_TYPEID_H
