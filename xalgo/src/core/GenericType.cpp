//
// Created by xgallom on 4/26/20.
//

#include <xalgo/core/GenericType.h>
#include <xalgo/core/TypeId.h>

namespace xalgo::core {
	GenericType::operator bool() const noexcept
	{
		return value && size && type >= TypeId::Invalid && type < XALGO_CONFIG_TYPE_ID_COUNT;
	}

	ConstGenericType::operator bool() const noexcept
	{
		return value && size && type >= TypeId::Invalid && type < XALGO_CONFIG_TYPE_ID_COUNT;
	}

	GenericType::operator ConstGenericType() const noexcept
	{
		return {
				.value = value,
				.size = size,
				.type = type
		};
	}
}
