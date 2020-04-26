#include "tests/tests.h"

#include <cstdio>
#include <cstring>

int main()
{
	static const std::unique_ptr<Test> Tests[] = {
			TestOperations::Create(),
			TestVariablesWorkspace::Create(),
			TestVariableOperation::Create(),
	};

	size_t maxNameLength = 0;
	for(const auto &test : Tests)
		maxNameLength = std::max(maxNameLength, strlen(test->name()));
	maxNameLength += 3;

	static const size_t Total = std::distance(std::begin(Tests), std::end(Tests));

	printf("Starting testing\n");

	size_t index = 1;
	for(const auto &test : Tests) {
		const char *const name = test->name();
		std::stringstream ss;
		ss << "\"" << name << "\":";

		auto testName = ss.str();
		testName.resize(maxNameLength, ' ');

		printf("\n[%3zu] out of [%3zu] - Running test %s ", index, Total, testName.c_str());

		try {
			test->execute();
		}
		catch(std::exception &exception) {
			printf("Failed\n");
			for(const auto &message : test->messages())
				printf("%s", message.c_str());
			fflush(stdout);

			fprintf(stderr, "%s\n", exception.what());
			fflush(stderr);

			return EXIT_FAILURE;
		}

		printf("Success\n");

		for(const auto &message : test->messages())
			printf("%s", message.c_str());

		++index;
	}

	return EXIT_SUCCESS;
}
