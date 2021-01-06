#include <stdlib.h>

#include "basic_operation.h"
#include "int_operation.h"
#include "unsigned_int_operation.h"
#include "utils.h"

void unsigned_int_add(bool * a, bool * b, bool * out) {
	int_add(a, b, out);
}

void unsigned_int_sub(bool * a, bool * b, bool * out) {
	int_sub(a, b, out);
}

void unsigned_int_mul(bool * a, bool * b, bool * out) {
	bool * product = mul(a, b, UNSIGNED_INT_LENGTH);
	for (int i = 0; i < UNSIGNED_INT_LENGTH; ++i)
		out[i] = product[i];
}

void unsigned_int_div(bool * a, bool * b, bool * out) {
	bool * quotient = divide(a, b, UNSIGNED_INT_LENGTH);
	for (int i = 0; i < UNSIGNED_INT_LENGTH; ++i)
		out[i] = quotient[UNSIGNED_INT_LENGTH + i];
}