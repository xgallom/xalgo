//
// Created by xgallom on 4/26/20.
//

#define XTEST_MODULE

#include "TestVariableOperation.h"

#include <xalgo/operations/Operations.h>
#include <xalgo/operations/EmptyOperations.h>
#include <xalgo/operations/UnaryOperations.h>
#include <xalgo/workspace/Workspace.h>

#include <cmath>

const char *TestVariableOperation::name()
{
	return "variable operation";
}

void TestVariableOperation::execute()
{
	static constexpr size_t BufferSize = sizeof(size_t) + sizeof("x");

	xalgo::Workspace::Class workspace;
	xalgo::Operations::Class operations;
	xalgo::Operations::Stack stack;

	uint8_t buffer[BufferSize] = {};
	info("Buffer size: ", BufferSize, " size_t: ", sizeof(size_t));

	const auto xId = workspace.variables.add(M_PI, "x");
	const auto yId = workspace.variables.add(M_PI_2, "y");
	const auto fId = workspace.variables.add(float(M_PI), "f");

	test(workspace.variables.size() == 3, "Variable insertion failed");

	operations.add(xalgo::EmptyOperations::variable, buffer, sizeof(buffer));
	operations.add(xalgo::UnaryOperations::minus);

	*reinterpret_cast<size_t *>(buffer) = xId;
	strcpy(reinterpret_cast<char *>(buffer) + sizeof(size_t), "x");

	test(operations.size() == 2, "Operations insertion failed");
	test(operations.parameterSize(0) == BufferSize, "Invalid parameter size: ", operations.parameterSize(0));



	test(operations.execute(&workspace, &stack), "Operations::Execute(var, -) failed");

	auto result = stack.pop<double>();
	test(bool(result), "Result is invalid");
	test(result() == -M_PI, "Result is not -pi: ", result(), " != ", -M_PI);


	*reinterpret_cast<size_t *>(buffer) = xId;
	strcpy(reinterpret_cast<char *>(buffer) + sizeof(size_t), "y");

	std::copy(buffer, buffer + BufferSize, operations.parameters().begin());


	test(operations.execute(&workspace, &stack), "Operations::Execute(var, -) failed");

	result = stack.pop<double>();
	test(bool(result), "Result is invalid");
	test(result() == -M_PI, "Result is not -pi: ", result(), " != ", -M_PI);


	*reinterpret_cast<size_t *>(buffer) = yId;
	strcpy(reinterpret_cast<char *>(buffer) + sizeof(size_t), "y");

	std::copy(buffer, buffer + BufferSize, operations.parameters().begin());


	test(operations.execute(&workspace, &stack), "Operations::Execute(var, -) failed");

	result = stack.pop<double>();
	test(bool(result), "Result is invalid");
	test(result() == -M_PI_2, "Result is not -pi_2: ", result(), " != ", -M_PI_2);


	*reinterpret_cast<size_t *>(buffer) = fId;
	strcpy(reinterpret_cast<char *>(buffer) + sizeof(size_t), "f");

	std::copy(buffer, buffer + BufferSize, operations.parameters().begin());


	test(operations.execute(&workspace, &stack), "Operations::Execute(var, -) failed");

	auto fResult = stack.pop<float>();
	test(bool(fResult), "Result is invalid");
	test(fResult() == float(-M_PI), "Result is not -pi_2: ", result(), " != ", float(-M_PI));



	operations.clear();
	operations.add(xalgo::EmptyOperations::variable, buffer, sizeof(buffer));
	operations.add(xalgo::UnaryOperations::minusPrimitive[xalgo::core::TypeId::Float]);


	test(operations.execute(&workspace, &stack), "Operations::Execute(var, -) failed");

	fResult = stack.pop<float>();
	test(bool(fResult), "Result is invalid");
	test(fResult() == float(-M_PI), "Result is not -pi_2: ", result(), " != ", float(-M_PI));


	*reinterpret_cast<size_t *>(buffer) = xId;
	strcpy(reinterpret_cast<char *>(buffer) + sizeof(size_t), "x");

	std::copy(buffer, buffer + BufferSize, operations.parameters().begin());


	test(!operations.execute(&workspace, &stack), "Operations::Execute(double, -float) did not fail");
}

