//
// Created by xgallom on 4/26/20.
//

#include <xalgo/core/GenericType.h>
#include <xalgo/core/TypeId.h>

namespace xalgo::core {
	GenericType::operator bool() const noexcept
	{
		return value && type >= TypeId::Invalid && type < XALGO_CONFIG_TYPE_ID_COUNT;
	}

	GenericType::operator ConstGenericType() const noexcept
	{
		return {
			.value = value,
			.type = type
		};
	}

	ConstGenericType::operator bool() const noexcept
	{
		return value && type >= TypeId::Invalid && type < XALGO_CONFIG_TYPE_ID_COUNT;
	}
}
