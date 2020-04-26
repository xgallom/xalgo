//
// Created by xgallom on 4/23/20.
//

#ifndef XALGO_XALGO_TESTS_SRC_TEST_H
#define XALGO_XALGO_TESTS_SRC_TEST_H

#include <memory>
#include <vector>
#include <string>
#include <sstream>

class Test {
	std::vector<std::string> m_messages = {};

public:
	virtual ~Test() = default;

	virtual const char *name() = 0;
	virtual void execute() = 0;

	inline const std::vector<std::string> &messages() const noexcept { return m_messages; }

protected:
	template<typename ... Args>
	void testImpl(bool check, Args ... message) const
	{
		if(!check) {
			std::stringstream ss;
			(ss << ... << std::forward<Args>(message));
			throw std::logic_error(ss.str());
		}
	}

	template<typename ... Args>
	void info(Args ... message)
	{
		std::stringstream ss;
		(ss << ... << std::forward<Args>(message)) << "\n";
		m_messages.push_back(ss.str());
	}
};

// Test macro to be used inside the execute function, and nowhere else, define XTEST_MODULE in your test source files
#ifdef XTEST_MODULE
#define test(check, ...) testImpl((check), __FILE__, ":", __LINE__, ": Test ", name(), " failed: ", __VA_ARGS__)
#endif

#endif //XALGO_XALGO_TESTS_SRC_TEST_H
