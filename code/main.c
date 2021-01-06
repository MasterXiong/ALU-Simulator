#include "float_test.h"
#include "int_test.h"
#include "unsigned_int_test.h"

int main() {
	test_int_add();
	test_int_sub();
	test_int_mul();
	test_int_div();

	test_unsigned_int_add();
	test_unsigned_int_sub();
	test_unsigned_int_mul();
	test_unsigned_int_div();

	test_float_add();
	test_float_sub();
	test_float_mul();
	test_float_div();
	
	return 0;
}