#include <stdlib.h>
#include <stdio.h>

#include "unsigned_int_operation.h"
#include "utils.h"

void test_equal_unsigned_int_add(unsigned int a, unsigned int b) {
	unsigned int add_true = a + b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * add_bits = (bool *)malloc(sizeof(bool) * 32);
	unsigned_int_add(a_bits, b_bits, add_bits);
	unsigned int add_actual = *(unsigned int *)(bits_to_num(add_bits));
	if (add_true != add_actual)
		printf("Test fail for %u + %u, true: %x, actual: %x\n", a, b, add_true, add_actual);
}

void test_unsigned_int_add() {
	printf("Test unsigned int add\n");
	// trivial cases
	test_equal_unsigned_int_add(0, 0);
	test_equal_unsigned_int_add(1, 0);
	test_equal_unsigned_int_add(5, 3);
	test_equal_unsigned_int_add(20, 3);
	// overflow cases
	test_equal_unsigned_int_add(0xffffffff, 0x00000002);
	test_equal_unsigned_int_add(0xf0000000, 0xf0000000);
	// random cases
	for (int i = 0; i < 100; ++i)
		test_equal_unsigned_int_add(rand(), rand());
	printf("Success!\n");
}

void test_equal_unsigned_int_sub(unsigned int a, unsigned int b) {
	unsigned int sub_true = a - b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * sub_bits = (bool *)malloc(sizeof(bool) * 32);
	unsigned_int_sub(a_bits, b_bits, sub_bits);
	unsigned int sub_actual = *(unsigned int *)(bits_to_num(sub_bits));
	if (sub_true != sub_actual)
		printf("Test fail for %u - %u, true: %x, actual: %x\n", a, b, sub_true, sub_actual);
}

void test_unsigned_int_sub() {
	printf("Test unsigned int sub\n");
	// trivial cases
	test_equal_unsigned_int_sub(0, 0);
	test_equal_unsigned_int_sub(1, 0);
	test_equal_unsigned_int_sub(5, 3);
	test_equal_unsigned_int_sub(20, 3);
	// overflow cases
	test_equal_unsigned_int_sub(0x00000000, 0x00000002);
	test_equal_unsigned_int_sub(0xf0000000, 0xff000000);
	// random cases
	for (int i = 0; i < 100; ++i)
		test_equal_unsigned_int_sub(rand(), rand());
	printf("Success!\n");
}

void test_equal_unsigned_int_mul(unsigned int a, unsigned int b) {
	unsigned int mul_true = a * b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * mul_bits = (bool *)malloc(sizeof(bool) * 32);
	unsigned_int_mul(a_bits, b_bits, mul_bits);
	unsigned int mul_actual = *(unsigned int *)(bits_to_num(mul_bits));
	if (mul_true != mul_actual)
		printf("Test fail for %u * %u, true: %x, actual: %x\n", a, b, mul_true, mul_actual);
}

void test_unsigned_int_mul() {
	printf("Test unsigned int mul\n");
	// trivial cases
	test_equal_unsigned_int_mul(0, 0);
	test_equal_unsigned_int_mul(1, 0);
	test_equal_unsigned_int_mul(5, 3);
	test_equal_unsigned_int_mul(20, 3);
	// overflow cases
	test_equal_unsigned_int_mul(0xffffffff, 0x00000002);
	test_equal_unsigned_int_mul(0x70000000, 0xff000000);
	// random cases
	for (int i = 0; i < 100; ++i)
		test_equal_unsigned_int_mul(rand(), rand());
	printf("Success!\n");
}

void test_equal_unsigned_int_div(unsigned int a, unsigned int b) {
	unsigned int div_true = a / b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * div_bits = (bool *)malloc(sizeof(bool) * 32);
	unsigned_int_div(a_bits, b_bits, div_bits);
	unsigned int div_actual = *(unsigned int *)(bits_to_num(div_bits));
	if (div_true != div_actual)
		printf("Test fail for %u / %u, true: %x, actual: %x\n", a, b, div_true, div_actual);
}

void test_unsigned_int_div() {
	printf("Test unsigned int div\n");
	// trivial cases
	//test_equal_unsigned_int_div(0, 0);
	//test_equal_unsigned_int_div(1, 0);
	test_equal_unsigned_int_div(0, 1);
	test_equal_unsigned_int_div(5, 1);
	test_equal_unsigned_int_div(4, 5);
	test_equal_unsigned_int_div(20, 3);
	// random cases
	for (int i = 0; i < 100; ++i)
		test_equal_unsigned_int_div(rand(), rand());
	printf("Success!\n");
}