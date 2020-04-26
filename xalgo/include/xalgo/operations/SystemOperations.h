//
// Created by xgallom on 4/26/20.
//

#ifndef XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_SYSTEMOPERATIONS_H
#define XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_SYSTEMOPERATIONS_H

#include "OperationsStack_fwd.h"
#include "../workspace/Workspace_fwd.h"

namespace xalgo::SystemOperations {
	bool invalid(Workspace::Class *, Operations::Stack *, const void *) noexcept;
}

#endif //XALGO_ROOT_XALGO_INCLUDE_XALGO_OPERATIONS_SYSTEMOPERATIONS_H
