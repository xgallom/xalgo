//
// Created by xgallom on 4/26/20.
//

#ifndef XALGO_ROOT_XALGO_TESTS_SRC_TESTS_TESTVARIABLESWORKSPACE_H
#define XALGO_ROOT_XALGO_TESTS_SRC_TESTS_TESTVARIABLESWORKSPACE_H

#include "../Test.h"

class TestVariablesWorkspace : public Test {
public:
	~TestVariablesWorkspace() final = default;

	const char *name() final;
	void execute() final;

	static inline std::unique_ptr<Test> Create() { return std::make_unique<TestVariablesWorkspace>(); };
};


#endif //XALGO_ROOT_XALGO_TESTS_SRC_TESTS_TESTVARIABLESWORKSPACE_H
