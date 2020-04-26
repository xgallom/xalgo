//
// Created by xgallom on 4/26/20.
//

#define XTEST_MODULE

#include "TestVariablesWorkspace.h"

#include <xalgo/workspace/VariablesWorkspace.h>
#include <math.h>

const char *TestVariablesWorkspace::name()
{
	return "variables workspace";
}

void TestVariablesWorkspace::execute()
{
	xalgo::Workspace::Variables variables;

	size_t xId = variables.add(M_PI, "x");
	test(variables.size() == 1, "Pi insertion failed");
	test(variables.byteSize() == sizeof(double),
			"Workspace does not contain a single double: ", variables.byteSize(), " != ", sizeof(double));
	test(xId == 0, "First variable id is not 0: ", xId);

	auto xResult = variables[xId];
	info("Result: ", xResult.type, ", ", reinterpret_cast<uint64_t>(xResult.value));
	test(bool(xResult), "Result is not valid");
	test(xResult.type == xalgo::core::TypeId::Double, "Result is not a double: ", xalgo::core::TypeId::Double);
	test(xResult.size == sizeof(double), "Result size mismatch: ", xResult.size, " != ", sizeof(double));

	auto xValue = *reinterpret_cast<const double *>(xResult.value);
	info("Value: ", xValue);
	test(xValue == M_PI, "Value is not pi: ", xValue, " != ", M_PI);


	size_t fId = variables.add(float(M_PI), "f");
	test(variables.size() == 2, "Float pi insertion failed");
	test(variables.byteSize() == sizeof(double) + sizeof(float),
			"Workspace does not contain variables: ", variables.byteSize(), " != ", sizeof(double) + sizeof(float));
	test(fId == 1, "Second variable is not 1: ", fId);

	auto fResult = variables["f"];
	info("Result: ", fResult.type, ", ", reinterpret_cast<uint64_t>(fResult.value));
	test(bool(fResult), "Result is not valid");
	test(fResult.type == xalgo::core::TypeId::Float, "Result is not a float: ", xalgo::core::TypeId::Float);
	test(fResult.size == sizeof(float), "Result size mismatch: ", fResult.size, " != ", sizeof(float));

	auto fValue = *reinterpret_cast<const float *>(fResult.value);
	info("Value: ", fValue);
	test(fValue == float(M_PI), "Value is not float pi: ", float(M_PI));


	test(variables.remove(fId), "Float removal returned false");
	test(variables.size() == 1, "Float removal failed");
	test(variables.byteSize() == sizeof(double),
			"Workspace does not contain a double: ", variables.byteSize(), " != ", sizeof(double));

	xResult = variables[xId];
	info("Result: ", xResult.type, ", ", reinterpret_cast<uint64_t>(xResult.value));
	test(bool(xResult), "Result is not valid");
	test(xResult.type == xalgo::core::TypeId::Double, "Result is not a double: ", xalgo::core::TypeId::Double);
	test(xResult.size == sizeof(double), "Result size mismatch: ", xResult.size, " != ", sizeof(double));

	xValue = *reinterpret_cast<const double *>(xResult.value);
	info("Value: ", xValue);
	test(xValue == M_PI, "Value is not pi: ", xValue, " != ", M_PI);

	xResult = variables["x"];
	info("Result: ", xResult.type, ", ", reinterpret_cast<uint64_t>(xResult.value));
	test(bool(xResult), "Result is not valid");
	test(xResult.type == xalgo::core::TypeId::Double, "Result is not a double: ", xalgo::core::TypeId::Double);
	test(xResult.size == sizeof(double), "Result size mismatch: ", xResult.size, " != ", sizeof(double));

	xValue = *reinterpret_cast<const double *>(xResult.value);
	info("Value: ", xValue);
	test(xValue == M_PI, "Value is not pi: ", xValue, " != ", M_PI);


	fId = variables.add(float(M_PI), "f");
	test(variables.size() == 2, "Float pi insertion failed");
	test(variables.byteSize() == sizeof(double) + sizeof(float),
		 "Workspace does not contain variables: ", variables.byteSize(), " != ", sizeof(double) + sizeof(float));
	test(fId == 2, "Third variable is not 2: ", fId);

	fResult = variables["f"];
	info("Result: ", fResult.type, ", ", reinterpret_cast<uint64_t>(fResult.value));
	test(bool(fResult), "Result is not valid");
	test(fResult.type == xalgo::core::TypeId::Float, "Result is not a float: ", xalgo::core::TypeId::Float);
	test(fResult.size == sizeof(float), "Result size mismatch: ", fResult.size, " != ", sizeof(float));

	fValue = *reinterpret_cast<const float *>(fResult.value);
	info("Value: ", fValue);
	test(fValue == float(M_PI), "Value is not float pi: ", float(M_PI));


	test(variables.remove(xId), "Double removal returned false");
	test(variables.size() == 1, "Double removal failed");
	test(variables.byteSize() == sizeof(float),
		 "Workspace does not contain a float: ", variables.byteSize(), " != ", sizeof(float));

	fResult = variables[fId];
	info("Result: ", fResult.type, ", ", reinterpret_cast<uint64_t>(fResult.value));
	test(bool(fResult), "Result is not valid");
	test(fResult.type == xalgo::core::TypeId::Float, "Result is not a float: ", xalgo::core::TypeId::Float);
	test(fResult.size == sizeof(float), "Result size mismatch: ", fResult.size, " != ", sizeof(float));

	fValue = *reinterpret_cast<const float *>(fResult.value);
	info("Value: ", fValue);
	test(fValue == float(M_PI), "Value is not float pi: ", float(M_PI));

	xId = variables.add(M_PI, "x");
	auto yId = variables.add(M_PI_2, "y");
	test(variables.size() == 3, "Pis insertion failed");
	test(variables.byteSize() == 2 * sizeof(double) + sizeof(float),
		 "Workspace does not contain variables: ", variables.byteSize(), " != ", 2 * sizeof(double) + sizeof(float));
	test(xId == 3 && yId == 4, "Variable ids are not 3 and 4: ", xId, ", ", yId);

	auto result = variables[fId];
	info("Result: ", result.type, ", ", reinterpret_cast<uint64_t>(result.value));
	test(bool(result), "Result is not valid");
	test(result.type == xalgo::core::TypeId::Float, "Result is not a float: ", xalgo::core::TypeId::Float);
	test(result.size == sizeof(float), "Result size mismatch: ", result.size, " != ", sizeof(float));

	double value = *reinterpret_cast<const float *>(result.value);
	info("Value: ", value);
	test(value == float(M_PI), "Value is not float pi: ", float(M_PI));


	result = variables[xId];
	info("Result: ", result.type, ", ", reinterpret_cast<uint64_t>(result.value));
	test(bool(result), "Result is not valid");
	test(result.type == xalgo::core::TypeId::Double, "Result is not a double: ", xalgo::core::TypeId::Double);
	test(result.size == sizeof(double), "Result size mismatch: ", result.size, " != ", sizeof(double));

	value = *reinterpret_cast<const double *>(result.value);
	info("Value: ", value);
	test(value == M_PI, "Value is not pi: ", M_PI);


	result = variables[yId];
	info("Result: ", result.type, ", ", reinterpret_cast<uint64_t>(result.value));
	test(bool(result), "Result is not valid");
	test(result.type == xalgo::core::TypeId::Double, "Result is not a double: ", xalgo::core::TypeId::Double);
	test(result.size == sizeof(double), "Result size mismatch: ", result.size, " != ", sizeof(double));

	value = *reinterpret_cast<const double *>(result.value);
	info("Value: ", value);
	test(value == M_PI_2, "Value is not pi_2: ", M_PI_2);


	test(variables.remove(xId), "Removing returned false");
	test(variables.size() == 2, "Removal failed");
	test(variables.byteSize() == sizeof(float) + sizeof(double),
		 "Workspace does not contain variables: ", variables.byteSize(), " != ", sizeof(float) + sizeof(double));


	result = variables[fId];
	info("Result: ", result.type, ", ", reinterpret_cast<uint64_t>(result.value));
	test(bool(result), "Result is not valid");
	test(result.type == xalgo::core::TypeId::Float, "Result is not a float: ", xalgo::core::TypeId::Float);
	test(result.size == sizeof(float), "Result size mismatch: ", result.size, " != ", sizeof(float));

	value = *reinterpret_cast<const float *>(result.value);
	info("Value: ", value);
	test(value == float(M_PI), "Value is not float pi: ", float(M_PI));


	result = variables[yId];
	info("Result: ", result.type, ", ", reinterpret_cast<uint64_t>(result.value));
	test(bool(result), "Result is not valid");
	test(result.type == xalgo::core::TypeId::Double, "Result is not a double: ", xalgo::core::TypeId::Double);
	test(result.size == sizeof(double), "Result size mismatch: ", result.size, " != ", sizeof(double));

	value = *reinterpret_cast<const double *>(result.value);
	info("Value: ", value);
	test(value == M_PI_2, "Value is not pi_2: ", M_PI_2);
}
