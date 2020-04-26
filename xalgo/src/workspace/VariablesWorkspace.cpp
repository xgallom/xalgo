//
// Created by xgallom on 4/25/20.
//

#include <xalgo/workspace/VariablesWorkspace.h>
#include <algorithm>

namespace xalgo::Workspace {
	void Variables::erase(size_t position)
	{
		const auto typeIndex = m_indexes[position];
		const auto size = this->size();
		const auto nameLength = strlen(m_names.data() + typeIndex.nameIndex) + 1;

		m_data.erase(m_data.begin() + typeIndex.index, m_data.begin() + typeIndex.index + typeIndex.size);
		m_names.erase(m_names.begin() + typeIndex.nameIndex, m_names.begin() + typeIndex.nameIndex + nameLength);

		for(size_t n = position + 1; n < size; ++n) {
			auto &to = m_indexes[n - 1];
			const auto &from = m_indexes[n];

			to = from;
			to.index -= typeIndex.size;
			to.nameIndex -= nameLength;
		}
		m_indexes.pop_back();

		m_ids.erase(m_ids.begin() + position);
	}

	size_t Variables::add(
			const uint8_t *data,
			size_t size,
			const char *name,
			size_t nameLength,
			size_t type)
	{
		const size_t id = m_nextId++;
		const TypeIndex typeIndex = {
				.index = byteSize(),
				.nameIndex = m_names.size(),
				.size = size,
				.type = type
		};

		m_data.insert(m_data.end(), data, data + size);
		m_ids.push_back(id);
		m_indexes.push_back(typeIndex);
		m_names.insert(m_names.end(), name, name + nameLength + 1);

		return id;
	}

	size_t Variables::add(
			const uint8_t *data,
			size_t size,
			const char *name,
			size_t type)
	{
		return add(data, size, name, strlen(name), type);
	}

	bool Variables::remove(size_t id)
	{
		const auto idIterator = std::lower_bound(
				m_ids.begin(),
				m_ids.end(),
				id
		);

		if(*idIterator != id || idIterator == m_ids.end())
			return false;

		erase(std::distance(m_ids.begin(), idIterator));

		return true;
	}

	bool Variables::remove(const char *name)
	{
		const auto *const names = m_names.data();

		const auto size = this->size();

		for(size_t n = 0; n < size; ++n) {
			if(strcmp(names + m_indexes[n].nameIndex, name) == 0) {
				erase(n);

				return true;
			}
		}

		return false;
	}

	core::GenericType Variables::operator[](size_t id) noexcept
	{
		const auto idIterator = std::lower_bound(
				m_ids.begin(),
				m_ids.end(),
				id
		);

		if(*idIterator != id || idIterator == m_ids.end())
			return {};

		const auto &typeIndex = m_indexes[std::distance(m_ids.begin(), idIterator)];

		return {
				.value = m_data.data() + typeIndex.index,
				.size = typeIndex.size,
				.type = typeIndex.type
		};
	}

	core::ConstGenericType Variables::operator[](size_t id) const noexcept
	{
		const auto idIterator = std::lower_bound(
				m_ids.begin(),
				m_ids.end(),
				id
		);

		if(*idIterator != id || idIterator == m_ids.end())
			return {};

		const auto &typeIndex = m_indexes[std::distance(m_ids.begin(), idIterator)];

		return {
				.value = m_data.data() + typeIndex.index,
				.size = typeIndex.size,
				.type = typeIndex.type
		};
	}

	core::GenericType Variables::operator[](const char *name) noexcept
	{
		const auto *const names = m_names.data();

		for(const auto &index : m_indexes) {
			if(strcmp(names + index.nameIndex, name) == 0) {
				return {
						.value = m_data.data() + index.index,
						.size = index.size,
						.type = index.type
				};
			}
		}

		return {};
	}

	core::ConstGenericType Variables::operator[](const char *name) const noexcept
	{
		const auto *const names = m_names.data();

		for(const auto &index : m_indexes) {
			if(strcmp(names + index.nameIndex, name) == 0) {
				return {
						.value = m_data.data() + index.index,
						.size = index.size,
						.type = index.type
				};
			}
		}

		return {};
	}

	[[nodiscard]] size_t Variables::byteSize() const noexcept
	{
		return m_data.size();
	}

	[[nodiscard]] size_t Variables::size() const noexcept
	{
		return m_indexes.size();
	}
}
