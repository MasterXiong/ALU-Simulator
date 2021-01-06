#include <stdbool.h>

bool * num_to_bits(void * num);
void * bits_to_num(bool * bits);

void half_adder(const bool a, const bool b, bool * sum, bool * carry_out);
void full_adder(const bool a, const bool b, const bool carry_in, bool * sum, bool * carry_out);

void left_shift(bool * bits, const int shift, const int length);
void right_shift(bool * bits, const int shift, const int length);

bool * add_one(bool * bits, int length);
bool * sub_one(bool * bits, int length);

void negative(bool * bits);

void multiplexer(bool * a, bool * b, bool * out, bool control, int length);

bool all_zeros(bool * bits, int length);