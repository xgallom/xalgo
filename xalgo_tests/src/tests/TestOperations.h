//
// Created by xgallom on 4/24/20.
//

#ifndef XALGO_ROOT_XALGO_TESTS_SRC_TESTS_TESTOPERATIONS_H
#define XALGO_ROOT_XALGO_TESTS_SRC_TESTS_TESTOPERATIONS_H

#include "../Test.h"

class TestOperations : public Test {
public:
	~TestOperations() final = default;

	const char *name() final;
	void execute() final;

	static inline std::unique_ptr<Test> Create() { return std::make_unique<TestOperations>(); };
};


#endif //XALGO_ROOT_XALGO_TESTS_SRC_TESTS_TESTOPERATIONS_H
