#include <stdbool.h>

#define SIGN_POS 31

#define EXPONENT_POS 23
#define EXPONENT_LENGTH 8
#define EXPONENT_BIAS 127

#define FRACTION_LENGTH 23

struct IEEE_format {
	bool sign;
	bool * fraction;
	bool * exponent;
	bool * fraction_complement;
};

struct IEEE_format bits_to_struct(bool * bits);
bool * struct_to_bits(struct IEEE_format num);

void float_add(bool * a, bool * b, bool * out);
void float_sub(bool * a, bool * b, bool * out);
void float_mul(bool * a, bool * b, bool * out);
void float_div(bool * a, bool * b, bool * out);
