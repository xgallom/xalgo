//
// Created by xgallom on 4/26/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_WORKSPACE_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_WORKSPACE_H

#include "VariablesWorkspace.h"

namespace xalgo::Workspace {
	struct Class {
		Class() = default;

		Variables variables = {};
	};
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_WORKSPACE_WORKSPACE_H
