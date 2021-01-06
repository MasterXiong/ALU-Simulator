#include <stdlib.h>

#include "basic_operation.h"
#include "int_operation.h"
#include "unsigned_int_operation.h"
#include "utils.h"

void int_add(bool * a, bool * b, bool * out) {
	bool * sum = add(a, b, INT_LENGTH, false);
	for (int i = 0; i < INT_LENGTH; ++i)
		out[i] = sum[i];
}

void int_sub(bool * a, bool * b, bool * out) {
	bool * diff = sub(a, b, INT_LENGTH);
	for (int i = 0; i < INT_LENGTH; ++i)
		out[i] = diff[i];
}

void int_mul(bool * a, bool * b, bool * out) {
	bool * a_abs = (bool *)malloc(sizeof(bool) * INT_LENGTH);
	bool * b_abs = (bool *)malloc(sizeof(bool) * INT_LENGTH);
	for (int i = 0; i < INT_LENGTH; ++i) {
		a_abs[i] = a[i];
		b_abs[i] = b[i];
	}
	if (a[31] == true)
		negative(a_abs);
	if (b[31] == true)
		negative(b_abs);
	unsigned_int_mul(a_abs, b_abs, out);
	if (a[31] ^ b[31])
		negative(out);
}

void int_div(bool * a, bool * b, bool * out) {
	bool * a_abs = (bool *)malloc(sizeof(bool) * INT_LENGTH);
	bool * b_abs = (bool *)malloc(sizeof(bool) * INT_LENGTH);
	for (int i = 0; i < INT_LENGTH; ++i) {
		a_abs[i] = a[i];
		b_abs[i] = b[i];
	}
	if (a[31] == true)
		negative(a_abs);
	if (b[31] == true)
		negative(b_abs);
	unsigned_int_div(a_abs, b_abs, out);
	if (a[31] ^ b[31])
		negative(out);
}