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

		core::GenericType top(size_t offset = 1) noexcept;
		core::ConstGenericType top(size_t offset = 1) const noexcept;
		void pop(size_t count = 1) noexcept;

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

		template<typename T>
		void push(const T &value)
		{
			m_indexes.push_back({
					.index = byteSize(),
					.type = core::TypeInfo<T>::Id,
			});

			const auto *const valuePtr = reinterpret_cast<const uint8_t *>(&value);

			m_data.insert(m_data.end(), valuePtr, valuePtr + core::TypeInfo<T>::Size);
		}

		void clear() noexcept;
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_OPERATIONSSTACK_H
