#include <stdlib.h>

#include "basic_operation.h"
#include "utils.h"

bool * add(bool * a, bool * b, int length, bool carry_in) {
	// use one additional bit to store the most significant bit
	// useful in some cases
	bool * sum = (bool *)malloc(sizeof(bool) * (length + 1));
	bool carry_out;
	for (int i = 0; i < length; ++i) {
		full_adder(a[i], b[i], carry_in, sum + i, &carry_out);
		carry_in = carry_out;
	}
	sum[length] = carry_out;
	return sum;
}

bool * sub(bool * a, bool * b, int length) {
	bool * b_inverse = (bool *)malloc(sizeof(bool) * length);
	for (int i = 0; i < length; ++i)
		b_inverse[i] = !b[i];
	bool * diff = add(a, b_inverse, length, true);
	return diff;
}

bool * mul(bool * a, bool * b, int length) {
	// initialization
	int product_length = length * 2;
	bool * product = (bool *)malloc(sizeof(bool) * product_length);
	bool * temp = (bool *)malloc(sizeof(bool) * product_length);
	for (int i = 0; i < product_length; ++i) {
		product[i] = false;
		temp[i] = false;
	}
	// perform add and left shift
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < length; ++j) {
			temp[j] = a[j] & b[i];
			temp[length + j] = false;
		}
		left_shift(temp, i, product_length);
		product = add(product, temp, product_length, false);
	}
	return product;
}

bool * divide(bool * a, bool * b, int length) {
	// initialize
	int double_length = 2 * length;
	bool * quotient = (bool *)malloc(sizeof(bool) * double_length);
	bool * remainer = (bool *)malloc(sizeof(bool) * double_length);
	for (int i = 0; i < double_length; ++i) {
		quotient[i] = false;
		remainer[i] = false;
	}
	bool * extended_b = (bool *)malloc(sizeof(bool) * double_length);
	for (int i = 0; i < length; ++i) {
		extended_b[i] = b[i];
		extended_b[length + i] = false;
	}
	// compute
	bool * temp = NULL;
	// compute the integer part of the quotient
	for (int shift = length - 1; shift >= 0; --shift) {
		left_shift(remainer, 1, double_length);
		remainer[0] = a[shift];
		temp = sub(remainer, extended_b, double_length);
		// remainer >= b
		if (temp[double_length - 1] == false) {
			for (int i = 0; i < double_length; ++i)
				remainer[i] = temp[i];
			quotient[length + shift] = true;
		}
	}
	// compute the decimal part of the quotient
	for (int shift = length - 1; shift >= 0; --shift) {
		left_shift(remainer, 1, double_length);
		temp = sub(remainer, extended_b, double_length);
		// remainer >= b
		if (temp[double_length - 1] == false) {
			for (int i = 0; i < double_length; ++i)
				remainer[i] = temp[i];
			quotient[shift] = true;
		}
	}
	return quotient;
}