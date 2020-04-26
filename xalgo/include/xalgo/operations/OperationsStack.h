//
// Created by xgallom on 4/25/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONSSTACK_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONSSTACK_H

#include "../core/Result.h"
#include "../core/TypeInfo.h"
#include "../core/TypeIndex.h"

#include <vector>
#include <cstdint>
#include <xalgo/core/GenericType.h>

namespace xalgo::Operations
{
	class Stack {
		std::vector<uint8_t> m_data = {};
		std::vector<core::TypeIndex> m_indexes = {};

		[[nodiscard]] uint8_t *data() noexcept;
		[[nodiscard]] const uint8_t *data() const noexcept;

		[[nodiscard]] core::TypeIndex *indexes() noexcept;
		[[nodiscard]] const core::TypeIndex *indexes() const noexcept;

		[[nodiscard]] core::TypeIndex &lastIndex(size_t offset = 1) noexcept;
		[[nodiscard]] const core::TypeIndex &lastIndex(size_t offset = 1) const noexcept;

	public:
		[[nodiscard]] size_t byteSize() const noexcept;
		[[nodiscard]] size_t size() const noexcept;

		[[nodiscard]] core::GenericType top(size_t offset = 1) noexcept;
		[[nodiscard]] core::ConstGenericType top(size_t offset = 1) const noexcept;
		void pop(size_t count = 1) noexcept;
		void push(const uint8_t *value, size_t size, size_t type);
		void push(const core::ConstGenericType &value);

		void clear() noexcept;

		template<typename T>
		[[nodiscard]] T &top(size_t offset = 1) noexcept
		{
			return *reinterpret_cast<T *>(data() + lastIndex(offset).index);
		}

		template<typename T>
		[[nodiscard]] const T &top(size_t offset = 1) const noexcept
		{
			return *reinterpret_cast<const T *>(data() + lastIndex(offset).index);
		}

		template<typename T>
		core::Result<T> pop() noexcept
		{
			if(!size())
				return {};

			const auto *index = &lastIndex();

			if(index->type != core::TypeInfo<T>::Id)
				return {};

			const T result = *reinterpret_cast<const T *>(data() + index->index);

			pop();

			return result;
		}

		template<typename T, typename std::enable_if_t<!std::is_base_of_v<core::GenericGenericType, T>, bool> = true>
		void push(const T &value)
		{
			push(reinterpret_cast<const uint8_t *>(&value), core::TypeInfo<T>::Size, core::TypeInfo<T>::Id);
		}
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONSSTACK_H
