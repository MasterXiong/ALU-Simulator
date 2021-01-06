#include <stdlib.h>

#include "basic_operation.h"
#include "utils.h"
#include "int_operation.h"

bool * num_to_bits(void * num) {
	int num_binary = *(int *)num;
	bool * bits = (bool *)malloc(sizeof(bool) * 32);
	for (int i = 0; i < 32; ++i) {
		bits[i] = (bool)(num_binary % 2);
		num_binary = num_binary >> 1;
	}
	return bits;
}

void * bits_to_num(bool * bits) {
	int * num = malloc(sizeof(int));
	for (int i = 31; i > 0; --i) {
		*num += (int)(bits[i]);
		*num = *num << 1;
	}
	*num += (int)(bits[0]);
	return (void *)num;
}

void half_adder(const bool a, const bool b, bool * sum, bool * carry_out) {
	*sum = a ^ b;
	*carry_out = a & b;
}

void full_adder(const bool a, const bool b, const bool carry_in, bool * sum, bool * carry_out) {
	bool half_sum, half_carry_1, half_carry_2;
	half_adder(a, b, &half_sum, &half_carry_1);
	half_adder(carry_in, half_sum, sum, &half_carry_2);
	*carry_out = half_carry_1 | half_carry_2;
}

void left_shift(bool * bits, const int shift, const int length) {
	for (int i = length - 1; i >= shift; --i)
		bits[i] = bits[i - shift];
	for (int i = shift - 1; i >= 0; --i)
		bits[i] = false;
}

void right_shift(bool * bits, const int shift, const int length) {
	bool sign_bit = bits[length - 1];
	for (int i = 0; i < length - shift; ++i)
		bits[i] = bits[i + shift];
	for (int i = length - shift; i < length; ++i)
		bits[i] = sign_bit;
}

bool * add_one(bool * bits, int length) {
    bool * one = (bool *)malloc(sizeof(bool) * length);
    for (int i = 1; i < length; ++i)
        one[i] = false;
    one[0] = true;
    bool * result = add(bits, one, length, false);
    return result;
}

bool * sub_one(bool * bits, int length) {
    bool * minus_one = (bool *)malloc(sizeof(bool) * length);
    for (int i = 0; i < length; ++i)
        minus_one[i] = true;
    bool * result = add(bits, minus_one, length, false);
    return result;
}

void negative(bool * bits) {
	for (int i = 0; i < 32; ++i)
		bits[i] = !bits[i];
	bool * one = (bool *)malloc(sizeof(bool) * 32);
	for (int i = 0; i < 32; ++i)
		one[i] = false;
	one[0] = true;
	int_add(bits, one, bits);
}

void multiplexer(bool * a, bool * b, bool * out, bool control, int length) {
	bool * p;
	if (control == false)
		p = a;
	else
		p = b;
	for (int i = 0; i < length; ++i)
		out[i] = p[i];
}

bool all_zeros(bool * bits, int length) {
	bool result = false;
	for (int i = 0; i < length; ++i)
		result = result | bits[i];
	return !result;
}