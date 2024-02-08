#pragma once
#include "Double1.h"

class Double1Test {
	Double1 a;
	Double1 b;
	Double1 c;
	void test_plus(bool suppress_output);
	void test_minus(bool suppress_output);
	void test_mult(bool suppress_output);
public:
	Double1Test() {};
	~Double1Test() {};
	void run_tests(bool suppress_output = true);
};

