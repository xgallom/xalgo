#include "tests/tests.h"

#include <cstdio>
#include <cstring>
#include <cassert>

static constexpr size_t MaxNameLength = 16;

int main()
{
	static const std::unique_ptr<Test> Tests [] = {
	};

	static const size_t Total = std::distance(std::begin(Tests), std::end(Tests));

	size_t index = 0;
	for(const auto &test : Tests) {
		const char *const name = test->name();
		const size_t nameLength = strlen(name);

		assert(nameLength <= MaxNameLength);

		char nameBuffer[MaxNameLength + 1] = {};
		memset(nameBuffer, ' ', MaxNameLength);
		strncpy(nameBuffer, name, nameLength);

		printf("Running test [%3zu] out of [%3zu] [%s] : ", index, Total, nameBuffer);

		try {
			test->execute();
		}
		catch(std::exception &exception) {
			printf("Failed\n");
			fflush(stdout);

			fprintf(stderr, "%s\n", exception.what());
			fflush(stderr);

			return EXIT_FAILURE;
		}

		printf("Success\n");

		++index;
	}

	return 0;
}
