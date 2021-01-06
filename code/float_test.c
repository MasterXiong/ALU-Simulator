#include <stdlib.h>
#include <stdio.h>

#include "float_operation.h"
#include "utils.h"

void test_equal_float_add(float a, float b) {
	float sum_true = a + b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * sum_bits = (bool *)malloc(sizeof(bool) * 32);
	float_add(a_bits, b_bits, sum_bits);
	float sum_actual = *(float *)(bits_to_num(sum_bits));
	if (sum_true != sum_actual)
		printf("Test fail for %f + %f, true: %x, actual: %x\n", a, b, *(int *)&sum_true, *(int *)&sum_actual);
}

void test_float_add() {
	printf("Test float add\n");
	// trivial cases
	test_equal_float_add(0., 0.);
	test_equal_float_add(1., 0.);
	//test_equal_float_add(-1, 0);
	// sum of two positive float
	test_equal_float_add(5., 3.);
	test_equal_float_add(5.4, 3.77);
	// sum of two negative float
	test_equal_float_add(-5., -3.);
	test_equal_float_add(-5.4, -3.77);
	// sum of one positive and one negative
	test_equal_float_add(3., -3.);
	test_equal_float_add(5., -3.);
	test_equal_float_add(-5., 3.);
	test_equal_float_add(5.4, -3.77);
	test_equal_float_add(-5.4, 3.77);
	// random cases
	for (int i = 0; i < 100; ++i) {
		float a = rand() * (rand() - RAND_MAX / 2) / (float)RAND_MAX;
		float b = rand() * (rand() - RAND_MAX / 2) / (float)RAND_MAX;
		test_equal_float_add(a, b);
	}
	printf("Success!\n");
}

void test_equal_float_sub(float a, float b) {
	float sub_true = a - b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * sub_bits = (bool *)malloc(sizeof(bool) * 32);
	float_sub(a_bits, b_bits, sub_bits);
	float sub_actual = *(float *)(bits_to_num(sub_bits));
	if (sub_true != sub_actual)
		printf("Test fail for %f - %f, true: %x, actual: %x\n", a, b, *(int *)&sub_true, *(int *)&sub_actual);
}

void test_float_sub() {
	printf("Test float sub\n");
	// trivial cases
	test_equal_float_add(0., 0.);
	test_equal_float_add(1., 0.);
	//test_equal_float_add(-1, 0);
	// two positive float
	test_equal_float_add(5., 3.);
	test_equal_float_add(5.4, 3.77);
	// two negative float
	test_equal_float_add(-5., -3.);
	test_equal_float_add(-5.4, -3.77);
	// one positive and one negative
	test_equal_float_add(3., -3.);
	test_equal_float_add(5., -3.);
	test_equal_float_add(-5., 3.);
	test_equal_float_add(5.4, -3.77);
	test_equal_float_add(-5.4, 3.77);
	// random cases
	for (int i = 0; i < 100; ++i) {
		float a = rand() * (rand() - RAND_MAX / 2) / (float)RAND_MAX;
		float b = rand() * (rand() - RAND_MAX / 2) / (float)RAND_MAX;
		test_equal_float_add(a, b);
	}
	printf("Success!\n");
}

void test_equal_float_mul(float a, float b) {
	float mul_true = a * b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * mul_bits = (bool *)malloc(sizeof(bool) * 32);
	float_mul(a_bits, b_bits, mul_bits);
	float mul_actual = *(float *)(bits_to_num(mul_bits));
	if (mul_true != mul_actual)
		printf("Test fail for %f * %f, true: %x, actual: %x\n", a, b, *(int *)&mul_true, *(int *)&mul_actual);
}

void test_float_mul() {
	printf("Test float mul\n");
	// trivial cases
	test_equal_float_mul(0.0, 0.0);
	test_equal_float_mul(1.0, 0);
	test_equal_float_mul(-1.0, 0);
	test_equal_float_mul(5., 3.5);
	test_equal_float_mul(-10.25, 5.33);
	test_equal_float_mul(-4.7, -3.6);
	// overflow cases
	//test_equal_float_mul(0x7fffffff, 0x0000000f);
	//test_equal_float_mul(0x80000000, 0x8000ffff);
	//test_equal_float_mul(0x80000000, 0x7fffffff);
	// random cases
	for (int i = 0; i < 100; ++i) {
		float a = rand() * (rand() - RAND_MAX / 2) / (float)RAND_MAX;
		float b = rand() * (rand() - RAND_MAX / 2) / (float)RAND_MAX;
		test_equal_float_mul(a, b);
	}
	for (int i = 0; i < 100; ++i) {
		float a = rand() / (float)RAND_MAX;
		float b = rand() / (float)RAND_MAX;
		test_equal_float_mul(a, b);
	}
	printf("Success!\n");
}

void test_equal_float_div(float a, float b) {
	float div_true = a / b;
	bool * a_bits = num_to_bits((void *)&a);
	bool * b_bits = num_to_bits((void *)&b);
	bool * div_bits = (bool *)malloc(sizeof(bool) * 32);
	float_div(a_bits, b_bits, div_bits);
	float div_actual = *(float *)(bits_to_num(div_bits));
	if (div_true != div_actual)
		printf("Test fail for %f / %f, true: %x, actual: %x\n", a, b, *(int *)&div_true, *(int *)&div_actual);
}

void test_float_div() {
	printf("Test float div\n");
	test_equal_float_div(5., 3.5);
	test_equal_float_div(3.5, 5.);
	test_equal_float_div(-10.25, 5.33);
	test_equal_float_div(5.33, -10.25);
	test_equal_float_div(-4.7, -3.6);
	test_equal_float_div(-3.6, -4.7);
	// random cases
	/*
	for (int i = 0; i < 100; ++i) {
		float a = rand() * (rand() - RAND_MAX / 2) / (float)RAND_MAX;
		float b = rand() * (rand() - RAND_MAX / 2) / (float)RAND_MAX;
		test_equal_float_div(a, b);
		test_equal_float_div(b, a);
	}
	for (int i = 0; i < 100; ++i) {
		float a = rand() / (float)RAND_MAX;
		float b = rand() / (float)RAND_MAX;
		test_equal_float_div(a, b);
		test_equal_float_div(b, a);
	}
	*/
	printf("Success!\n");
}
