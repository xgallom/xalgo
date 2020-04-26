//
// Created by xgallom on 4/26/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_GENERICTYPE_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_GENERICTYPE_H

#include "TypeId.h"

#include <cstddef>
#include <cstdint>

namespace xalgo::core {
	struct ConstGenericType {
		const uint8_t *value = {};
		size_t type = TypeId::Invalid;

		explicit operator bool() const noexcept;
	};

	struct GenericType {
		uint8_t *value = {};
		size_t type = TypeId::Invalid;

		explicit operator bool() const noexcept;
		operator ConstGenericType() const noexcept;
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_CORE_GENERICTYPE_H
