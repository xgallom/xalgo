//
// Created by xgallom on 4/24/20.
//

#define XTEST_MODULE

#include "TestOperations.h"

#include <xalgo/operations/Operations.h>
#include <xalgo/operations/EmptyOperations.h>
#include <xalgo/operations/UnaryOperations.h>

#include <cmath>

const char *TestOperations::name()
{
	return "operations";
}

void TestOperations::execute()
{
	xalgo::Operations::Class operations;

	info("Adding constant(pi): ", M_PI);
	operations.add(xalgo::EmptyOperations::constant, M_PI);
	test(operations.size() == 1, "Operations::Add(constant, pi) failed");
	test(operations.operationFunction(0) ==
		 reinterpret_cast<xalgo::Operations::Function::Interface>(&xalgo::EmptyOperations::constant),
		 "Operations[0] != constant");
	test(operations.parameterSize(0) == sizeof(double), "Operations[0].parameterSize != sizeof(double)");

	info("Adding generic Unary::minus");
	operations.add(xalgo::UnaryOperations::minus);
	test(operations.size() == 2, "Operations::Add(Unary::minus) failed");
	test(operations.operationFunction(1) == xalgo::UnaryOperations::minus, "Operations[1] != Unary::minus");
	test(operations.parameterSize(1) == 0, "Operations[1].parameterSize != 0");

	info("Creating empty Stack");
	xalgo::Operations::Stack stack;

	info("Executing with empty stack");
	test(operations.execute(&stack), "Operations::Execute(emptyStack) failed");

	auto result = stack.pop<double>();
	info("Result<double>: ", bool(result), ", ", result());
	test(bool(result), "Stack::Pop(double) failed");
	info("Comparing with -pi: ", -M_PI);
	test(result() == -M_PI, "Operations::Execute(emptyStack): ", result(), " != ", -M_PI);


	info("Checking if stack popped");
	test(stack.size() == 0, "Stack popped incorrectly");
	test(stack.byteSize() == 0, "Stack popped, bud removed incorrect length");

	info("Rerunning on empty stack");
	test(operations.execute(&stack), "Operations::Execute(emptyStack) failed");

	info("Topping(double) result");
	double top = stack.top<double>();
	info("top<double>: ", top);
	test(top == -M_PI, "Stack::Top<double> failed: ", top, " != ", -M_PI);


	info("Rerunning on non-empty stack");
	test(operations.execute(&stack), "Operations::Execute(nonEmptyStack) failed");

	test(stack.size() == 2, "Stack does not contain 2 elements: ", stack.size());
	test(stack.byteSize() == sizeof(double) * 2,
		 "Stack does not contain 2 doubles: ", stack.byteSize(), " != ", sizeof(double) * 2);

	result = stack.pop<double>();
	info("Result<double>: ", bool(result), ", ", result());
	test(bool(result), "Stack::Pop(double) failed");
	info("Comparing with -pi: ", -M_PI);
	test(result() == -M_PI, "Operations::Execute(emptyStack): ", result(), " != ", -M_PI);

	info("Topping(double) previous result");
	top = stack.top<double>();
	info("top<double>: ", top);
	test(top == result(), "top[0] == pop[1] failed: ", top, " != ", -M_PI);


	info("Clearing operations");
	operations.clear();
	test(operations.size() == 0, "Operations::Clear did not clear");

	info("Adding Unary::minusDouble");
	operations.add(xalgo::UnaryOperations::minusPrimitive[xalgo::core::TypeId::Double]);
	test(operations.size() == 1, "Operations::Add(Unary::minus) failed");
	test(operations.operationFunction(0) == xalgo::UnaryOperations::minusDouble, "Operations[0] != Unary::minusDouble");
	test(operations.parameterSize(0) == 0, "Operations[0].parameterSize != 0");

	info("Executing just Unary::minus on non empty stack");
	test(operations.execute(&stack), "Operations::Execute(nonEmptyStack) failed");
	test(stack.size() == 1, "Operations::Execute did not consume previous value");
	test(stack.byteSize() == sizeof(double),
		 "Stack does not contain a single double: ", stack.byteSize(), " != ", sizeof(double));

	result = stack.pop<double>();
	info("Result<double>: ", bool(result), ", ", result());
	test(bool(result), "Stack::Pop(double) failed");
	info("Comparing with pi: ", M_PI);
	test(result() == M_PI, "Operations::Execute(nonEmptyStack): ", result(), " != ", M_PI);


	info("Clearing operations");
	operations.clear();
	test(operations.size() == 0, "Operations::Clear did not clear");

	info("Adding Unary::minusFloat");
	operations.add(xalgo::UnaryOperations::minusPrimitive[xalgo::core::TypeId::Float]);
	test(operations.size() == 1, "Operations::Add(Unary::minus) failed");
	test(operations.operationFunction(0) == xalgo::UnaryOperations::minusFloat, "Operations[0] != Unary::minusFloat");
	test(operations.parameterSize(0) == 0, "Operations[0].parameterSize != 0");

	stack.push<float>(M_PI);
	info("Executing just Unary::minusFloat on stack with a float");
	test(operations.execute(&stack), "Operations::Execute(floatStack) failed");
	test(stack.size() == 1, "Operations::Execute did not consume previous value");
	test(stack.byteSize() == sizeof(float),
		 "Stack does not contain a single float: ", stack.byteSize(), " != ", sizeof(float));

	info("Topping(float) result");
	float topFloat = stack.top<float>();
	info("top<float>: ", topFloat);
	test(topFloat == float(-M_PI), "top[0] == -float(M_PI) failed: ", topFloat, " != ", float(-M_PI));

	info("Pushing a double onto stack");
	stack.push(M_PI);
	test(stack.size() == 2, "Stack with a double and float does not have size 2");
	test(stack.byteSize() == sizeof(double) + sizeof(float),
		 "Stack does not have a correct size: ", stack.byteSize(), " != ", sizeof(double) + sizeof(float));

	info("Executing Unary::minusFloat on a double");
	test(!operations.execute(&stack), "Executing Unary::minusFloat on a double succeeded");
	test(stack.size() == 3, "Execution removed the double from stack");
	info("Current stack: ",
		 stack.top<float>(1), ", ",
		 stack.top<double>(2), ", ",
		 stack.top<float>(3)
	);
	test(stack.top<float>(1) == -0.f && stack.top<double>(2) == M_PI, stack.top<float>(3) == float(-M_PI),
	        "Stack state invalid, should be: ", -0.f, ", ", M_PI, ", ", float(-M_PI));

	info("Replacing with generic Unary::minus");
	operations.clear();
	operations.add(xalgo::UnaryOperations::minus);

	info("Executing for every stack entry");
	for(size_t n = 0; n < 3; ++n) {
		test(operations.execute(&stack), "Generic execute failed with entry: ", n);

		if(n == 0) {
			const auto value = stack.pop<float>();
			test(bool(value), "Popping result on entry ", n, " failed");
			test(value() == 0.f, "Invalud value: ", value(), " != ", 0.f);
			info("Result at entry ", n, ": ", value());
		}
		else if(n == 1) {
			const auto value = stack.pop<double>();
			test(bool(value), "Popping result on entry ", n, " failed");
			test(value() == -M_PI, "Invalud value: ", value(), " != ", -M_PI);
			info("Result at entry ", n, ": ", value());
		}
		else {
			const auto value = stack.pop<float>();
			test(bool(value), "Popping result on entry ", n, " failed");
			test(value() == float(M_PI), "Invalud value: ", value(), " != ", float(M_PI));
			info("Result at entry ", n, ": ", value());
		}
	}
}
