//
// Created by xgallom on 4/25/20.
//

#include <xalgo/operations/OperationsStack.h>

namespace xalgo::Operations {
	uint8_t *Stack::data() noexcept
	{
		return m_data.data();
	}

	const uint8_t *Stack::data() const noexcept
	{
		return m_data.data();
	}

	core::TypeIndex *Stack::indexes() noexcept
	{
		return m_indexes.data();
	}

	const core::TypeIndex *Stack::indexes() const noexcept
	{
		return m_indexes.data();
	}

	core::TypeIndex &Stack::lastIndex(size_t offset) noexcept
	{
		return m_indexes[size() - offset];
	}

	const core::TypeIndex &Stack::lastIndex(size_t offset) const noexcept
	{
		return m_indexes[size() - offset];
	}

	[[nodiscard]] size_t Stack::byteSize() const noexcept
	{
		return m_data.size();
	}

	size_t Stack::size() const noexcept
	{
		return m_indexes.size();
	}

	core::GenericType Stack::top(size_t offset) noexcept
	{
		if(int32_t(size()) - int32_t(offset) < 0)
			return {};

		const auto &index = lastIndex(offset);

		return {
				.value = data() + index.index,
				.size = index.size,
				.type = index.type
		};
	}

	core::ConstGenericType Stack::top(size_t offset) const noexcept
	{
		if(int32_t(size()) - int32_t(offset) < 0)
			return {};

		const auto &index = lastIndex(offset);

		return {
				.value = data() + index.index,
				.size = index.size,
				.type = index.type
		};
	}

	void Stack::pop(size_t count) noexcept
	{
		m_data.erase(m_data.begin() + lastIndex(count).index, m_data.end());
		m_indexes.erase(m_indexes.end() - count, m_indexes.end());
	}

	void Stack::push(const uint8_t *value, size_t size, size_t type)
	{
		m_indexes.push_back(
				{
						.index = byteSize(),
						.size = size,
						.type = type,
				}
		);

		m_data.insert(m_data.end(), value, value + size);
	}

	void Stack::push(const core::ConstGenericType &value)
	{
		push(value.value, value.size, value.type);
	}

	void Stack::clear() noexcept
	{
		m_data.clear();
		m_indexes.clear();
	}
}
