#include <stdlib.h>
#include <stdio.h>

#include "int_operation.h"
#include "utils.h"

void test_equal_int_add(int a, int b) {
	int sum_true = a + b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * sum_bits = (bool *)malloc(sizeof(bool) * 32);
	int_add(a_bits, b_bits, sum_bits);
	int sum_actual = *(int *)(bits_to_num(sum_bits));
	if (sum_true != sum_actual)
		printf("Test fail for %d + %d, true: %x, actual: %x\n", a, b, sum_true, sum_actual);
}

void test_int_add() {
	printf("Test int add\n");
	// trivial cases
	test_equal_int_add(0, 0);
	test_equal_int_add(1, 0);
	test_equal_int_add(-1, 0);
	test_equal_int_add(5, 3);
	test_equal_int_add(-10, 5);
	test_equal_int_add(-20, -3);
	// overflow cases
	test_equal_int_add(0x7fffffff, 0x0000000f);
	test_equal_int_add(0x80000000, 0xfffffff0);
	// random cases
	for (int i = 0; i < 100; ++i)
		test_equal_int_add(rand() - (int)(RAND_MAX / 2), rand() - (int)(RAND_MAX / 2));
	printf("Success!\n");
}

void test_equal_int_sub(int a, int b) {
	int sub_true = a - b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * sub_bits = (bool *)malloc(sizeof(bool) * 32);
	int_sub(a_bits, b_bits, sub_bits);
	int sub_actual = *(int *)(bits_to_num(sub_bits));
	if (sub_true != sub_actual)
		printf("Test fail for %d - %d, true: %x, actual: %x\n", a, b, sub_true, sub_actual);
}

void test_int_sub() {
	printf("Test int sub\n");
	// trivial cases
	test_equal_int_sub(0, 0);
	test_equal_int_sub(1, 0);
	test_equal_int_sub(-1, 0);
	test_equal_int_sub(5, 3);
	test_equal_int_sub(-10, 5);
	test_equal_int_sub(-20, -3);
	// overflow cases
	test_equal_int_sub(0x7fffffff, 0xfffffff0);
	test_equal_int_sub(0x80000000, 0x0000ffff);
	// random cases
	for (int i = 0; i < 100; ++i)
		test_equal_int_sub(rand() - (int)(RAND_MAX / 2), rand() - (int)(RAND_MAX / 2));
	printf("Success!\n");
}

void test_equal_int_mul(int a, int b) {
	int mul_true = a * b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * mul_bits = (bool *)malloc(sizeof(bool) * 32);
	int_mul(a_bits, b_bits, mul_bits);
	int mul_actual = *(int *)(bits_to_num(mul_bits));
	if (mul_true != mul_actual)
		printf("Test fail for %d * %d, true: %x, actual: %x\n", a, b, mul_true, mul_actual);
}

void test_int_mul() {
	printf("Test int mul\n");
	// trivial cases
	test_equal_int_mul(0, 0);
	test_equal_int_mul(1, 0);
	test_equal_int_mul(-1, 0);
	test_equal_int_mul(5, 3);
	test_equal_int_mul(-10, 5);
	test_equal_int_mul(-4, -3);
	// overflow cases
	test_equal_int_mul(0x7fffffff, 0x0000000f);
	test_equal_int_mul(0x80000000, 0x8000ffff);
	test_equal_int_mul(0x80000000, 0x7fffffff);
	// random cases
	for (int i = 0; i < 100; ++i)
		test_equal_int_mul(rand() - (int)(RAND_MAX / 2), rand() - (int)(RAND_MAX / 2));
	printf("Success!\n");
}

void test_equal_int_div(int a, int b) {
	int div_true = a / b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * div_bits = (bool *)malloc(sizeof(bool) * 32);
	int_div(a_bits, b_bits, div_bits);
	int div_actual = *(int *)(bits_to_num(div_bits));
	if (div_true != div_actual)
		printf("Test fail for %d / %d, true: %x, actual: %x\n", a, b, div_true, div_actual);
}

void test_int_div() {
	printf("Test int div\n");
	// trivial cases
	test_equal_int_div(0, 1);
	test_equal_int_div(3, 2);
	test_equal_int_div(5, -1);
	test_equal_int_div(-4, 5);
	test_equal_int_div(-20, -3);
	// random cases
	for (int i = 0; i < 100; ++i)
		test_equal_int_div(rand(), rand());
	printf("Success!\n");
}