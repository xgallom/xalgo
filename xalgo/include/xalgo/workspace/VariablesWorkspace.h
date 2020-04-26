//
// Created by xgallom on 4/25/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_VARIABLESWORKSPACE_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_VARIABLESWORKSPACE_H

#include "../core/TypeInfo.h"

#include <vector>
#include <string>
#include <memory>
#include <cstring>
#include <xalgo/core/GenericType.h>

namespace xalgo::Workspace {
	struct TypeIndex {
		size_t index;
		size_t nameIndex;
		size_t size;
		size_t type;
	};

	class Variables {
		std::vector<uint8_t> m_data = {};
		std::vector<size_t> m_ids = {};
		std::vector<TypeIndex> m_indexes = {};
		std::vector<char> m_names = {};

		size_t m_nextId = {};

		void erase(size_t position);
	public:
		size_t add(
				const uint8_t *data,
				size_t size,
				const char *name,
				size_t nameLength,
				size_t type
		);

		size_t add(
				const uint8_t *data,
				size_t size,
				const char *name,
				size_t type
		);

		template<typename T>
		size_t add(
				const T &value,
				const char *name,
				size_t nameLength)
		{
			return add(
					reinterpret_cast<const uint8_t *>(&value),
					core::TypeInfo<T>::Size,
					name,
					nameLength,
					core::TypeInfo<T>::Id
			);
		}

		template<typename T>
		size_t add(
				const T &value,
				const char *name)
		{
			return add(
					reinterpret_cast<const uint8_t *>(&value),
					core::TypeInfo<T>::Size,
					name,
					strlen(name),
					core::TypeInfo<T>::Id
			);
		}

		bool remove(size_t id);
		bool remove(const char *name);

		core::GenericType operator[](size_t id) noexcept;
		core::ConstGenericType operator[](size_t id) const noexcept;
		core::GenericType operator[](const char *name) noexcept;
		core::ConstGenericType operator[](const char *name) const noexcept;

		[[nodiscard]] size_t byteSize() const noexcept;
		[[nodiscard]] size_t size() const noexcept;
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_VARIABLESWORKSPACE_H
