//
// Created by xgallom on 4/25/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_VARIABLESWORKSPACE_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_VARIABLESWORKSPACE_H

#include <vector>
#include <string>
#include <memory>

namespace xalgo::Workspace {
	struct TypeIndex {
		size_t index;
		size_t type;
	};

	class Variables {
		std::vector<uint32_t> m_data;
		std::vector<size_t> m_ids;
		std::vector<TypeIndex> m_indexes;
		std::vector<std::string> m_names;

	public:
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_VARIABLESWORKSPACE_H
