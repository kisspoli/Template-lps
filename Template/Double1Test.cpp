#include "Double1Test.h"
#include <iostream>
#include <cassert>
#include "Double1.h"

void Double1Test::test_plus(bool suppress_output)
{
	// 1 + 1 = 2
	a = Double1(1, 0, 0, false);
	b = Double1(1, 0, 0, false);
	c = a + b;
	if(!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "2");

	// 1.1 + 1.01 = 2.11
	a = Double1(1, 1, 0, false);
	b = Double1(1, 1, 1, false);
	c = a + b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "2.11");

	// 1.01 + 1.1 = 2.11
	a = Double1(1, 1, 1, false);
	b = Double1(1, 1, 0, false);
	c = a + b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "2.11");

	// 1.05 + 1.005 = 2.055
	a = Double1(1, 5, 1, false);
	b = Double1(1, 5, 2, false);
	c = a + b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "2.055");

	// 1.005 + 1.05 = 2.055
	a = Double1(1, 5, 2, false);
	b = Double1(1, 5, 1, false);
	c = a + b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "2.055");

	// 1.005 + 1.005 = 2.01
	a = Double1(1, 5, 2, false);
	b = Double1(1, 5, 2, false);
	c = a + b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "2.01");

	// 1.5 + 1.5 = 3
	a = Double1(1, 5, 0, false);
	b = Double1(1, 5, 0, false);
	c = a + b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "3");

	// 1.99 + 1.99 = 3.98
	a = Double1(1, 99, 0, false);
	b = Double1(1, 99, 0, false);
	c = a + b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "3.98");
}

void Double1Test::test_minus(bool suppress_output)
{
	// 1 - 1 = 0
	a = Double1(1, 0, 0, false);
	b = Double1(1, 0, 0, false);
	c = a - b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "0");

	// 1.1 - 1.01 = 0.09
	a = Double1(1, 1, 0, false);
	b = Double1(1, 1, 1, false);
	c = a - b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "0.09");

	// 1.01 - 1.1 = -0.09
	a = Double1(1, 1, 1, false);
	b = Double1(1, 1, 0, false);
	c = a - b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "-0.09");

	// 1.05 - 1.005 = 0.045
	a = Double1(1, 5, 1, false);
	b = Double1(1, 5, 2, false);
	c = a - b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "0.045");

	// 1.005 - 1.05 = -0.045
	a = Double1(1, 5, 2, false);
	b = Double1(1, 5, 1, false);
	c = a - b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "-0.045");

	// 0 - 0.01 = -0.01
	a = Double1(0, 0, 0, false);
	b = Double1(0, 1, 1, false);
	c = a - b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "-0.01");

	// 1.05 - 1.7 = -0.65
	a = Double1(1, 5, 1, false);
	b = Double1(1, 7, 0, false);
	c = a - b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "-0.65");

	// 3 - 3.99 = -0.99
	a = Double1(3, 0, 0, false);
	b = Double1(3, 99, 0, false);
	c = a - b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "-0.99");
}

void Double1Test::test_mult(bool suppress_output)
{
	// 1 * 1 = 1
	a = Double1(1, 0, 0, false);
	b = Double1(1, 0, 0, false);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "1");

	// 1.1 * 1.01 = 1.111
	a = Double1(1, 1, 0, false);
	b = Double1(1, 1, 1, false);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "1.111");

	// 1.01 * 1.1 = 1.111
	a = Double1(1, 1, 1, false);
	b = Double1(1, 1, 0, false);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "1.111");

	// 1.05 * 1.005 = 1.05525
	a = Double1(1, 5, 1, false);
	b = Double1(1, 5, 2, false);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "1.05525");

	// 1.005 * 1.05 = 1.05525
	a = Double1(1, 5, 2, false);
	b = Double1(1, 5, 1, false);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "1.05525");

	// 0 * 0.01 = 0
	a = Double1(0, 0, 0, false);
	b = Double1(0, 1, 1, false);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "0");

	// 1.05 * 1.7 = 1.785
	a = Double1(1, 5, 1, false);
	b = Double1(1, 7, 0, false);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "1.785");

	// 3.99 * -3.99 = -15.9201
	a = Double1(3, 99, 0, false);
	b = Double1(3, 99, 0, true);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "-15.9201");

	// 3.03 * 3.003 = 9.09909
	a = Double1(3, 3, 1, false);
	b = Double1(3, 3, 2, false);
	c = a * b;
	if (!suppress_output)
		std::cout << c.to_string() << std::endl;
	assert(c.to_string() == "9.09909");
}

void Double1Test::run_tests(bool suppress_output) {
	test_plus(suppress_output);
	test_minus(suppress_output);
	test_mult(suppress_output);
}
