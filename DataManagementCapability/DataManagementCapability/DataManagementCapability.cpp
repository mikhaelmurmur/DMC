// DataManagementCapability.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DMC.hpp"

struct test_struct
{
	int internal_value;
};

int main()
{
	data_management::DMC dmc;
	test_struct test;
	test.internal_value = 1;
	dmc.registerObject<test_struct>();
	auto index = dmc.update(test);

	auto element = dmc.read<test_struct>(index);
	test.internal_value = 2;
	dmc.update(index, test);

	element = dmc.read<test_struct>(index);

	return 0;
}

