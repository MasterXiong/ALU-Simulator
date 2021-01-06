#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "basic_operation.h"
#include "float_operation.h"
#include "utils.h"

struct IEEE_format bits_to_struct(bool * bits) {
    struct IEEE_format num;
    num.sign = bits[SIGN_POS];
    num.fraction = (bool *)malloc(sizeof(bool) * (FRACTION_LENGTH + 1));
    for (int i = 0; i < FRACTION_LENGTH; ++i)
        num.fraction[i] = bits[i];
    num.fraction[FRACTION_LENGTH] = true;
    num.exponent = (bool *)malloc(sizeof(bool) * (EXPONENT_LENGTH));
    for (int i = 0; i < EXPONENT_LENGTH; ++i)
        num.exponent[i] = bits[EXPONENT_POS + i];
    num.fraction_complement = (bool *)malloc(sizeof(bool) * (FRACTION_LENGTH + 2));
    for (int i = 0; i < FRACTION_LENGTH + 1; ++i)
        num.fraction_complement[i] = num.fraction[i];
    num.fraction_complement[FRACTION_LENGTH + 1] = false;
    if (num.sign) {
        for (int i = 0; i < FRACTION_LENGTH + 2; ++i)
            num.fraction_complement[i] = !num.fraction_complement[i];
        num.fraction_complement = add_one(num.fraction_complement, FRACTION_LENGTH + 2);
    }
    return num;
}

bool * struct_to_bits(struct IEEE_format num) {
    bool * bits = (bool *)malloc(sizeof(bool) * 32);
    bits[SIGN_POS] = num.sign;
    for (int i = 0; i < EXPONENT_LENGTH; ++i)
        bits[EXPONENT_POS + i] = num.exponent[i];
    for (int i = 0; i < FRACTION_LENGTH; ++i)
        bits[i] = num.fraction[i];
    return bits;
}

void float_add(bool * a, bool * b, bool * out) {
    // convert bits to IEEE754-format struct
    struct IEEE_format a_struct = bits_to_struct(a);
    struct IEEE_format b_struct = bits_to_struct(b);
    struct IEEE_format sum_struct;
    sum_struct.fraction = (bool *)malloc(sizeof(bool) * (FRACTION_LENGTH + 1));
    sum_struct.exponent = (bool *)malloc(sizeof(bool) * (EXPONENT_LENGTH));
    // compare the two exponents
    bool * exponent_diff = sub(a_struct.exponent, b_struct.exponent, EXPONENT_LENGTH);
    int shift = -(int)exponent_diff[EXPONENT_LENGTH - 1] * (int)pow(2, EXPONENT_LENGTH - 1);
    for (int i = 0; i < EXPONENT_LENGTH - 1; ++i)
        shift += (int)exponent_diff[i] * (int)pow(2, i);
    if (shift < 0)
        shift = -shift;
    // (control_signal == 1) means that a's exponent is smaller than b's
    bool is_negative = exponent_diff[EXPONENT_LENGTH - 1];
    // we need to right shift the fraction of the operand with smaller exponent
    // to align with the other operand's fraction
    // add another additional bit to deal with negative number
    bool * small_fraction = (bool *)malloc(sizeof(bool) * (FRACTION_LENGTH + 2));
    bool * large_fraction = (bool *)malloc(sizeof(bool) * (FRACTION_LENGTH + 2));
    // assign the two operands to the smaller and larger fraction, and right shift the smaller one
    if (a_struct.sign ^ b_struct.sign) {
        multiplexer(a_struct.fraction_complement, b_struct.fraction_complement, small_fraction, !is_negative, FRACTION_LENGTH + 2);
        multiplexer(a_struct.fraction_complement, b_struct.fraction_complement, large_fraction, is_negative, FRACTION_LENGTH + 2);
    } else {
        multiplexer(a_struct.fraction, b_struct.fraction, small_fraction, !is_negative, FRACTION_LENGTH + 1);
        multiplexer(a_struct.fraction, b_struct.fraction, large_fraction, is_negative, FRACTION_LENGTH + 1);
        small_fraction[FRACTION_LENGTH + 1] = false;
        large_fraction[FRACTION_LENGTH + 1] = false;
    }
    // right shift the smaller fraction
    bool rounding_bit = small_fraction[shift - 1];
    right_shift(small_fraction, shift, FRACTION_LENGTH + 2);
    if (shift > 0) {
        if (rounding_bit)
            small_fraction = add_one(small_fraction, FRACTION_LENGTH + 2);
    }
    // add the aligned fractions
    bool * fraction_sum = add(small_fraction, large_fraction, FRACTION_LENGTH + 2, false);        
    // The result's exponent equals to the larger exponent of the two operands
    multiplexer(a_struct.exponent, b_struct.exponent, sum_struct.exponent, is_negative, EXPONENT_LENGTH);
    // post process
    if (a_struct.sign ^ b_struct.sign) {
        // for sum of numbers with different signs, the MSB in fraction_sum represents the sign of their sum
        sum_struct.sign = fraction_sum[FRACTION_LENGTH + 1];
        // convert two's complement to its absolute value
        if (sum_struct.sign) {
            for (int i = 0; i < FRACTION_LENGTH + 2; ++i)
                fraction_sum[i] = !fraction_sum[i];
            fraction_sum = add_one(fraction_sum, FRACTION_LENGTH + 2);
        }
        // check if left shift is required
        int shift_bits = 0;
        for (int i = FRACTION_LENGTH; i >= 0; --i) {
            if (fraction_sum[i] == false) {
                shift_bits += 1;
                sum_struct.exponent = sub_one(sum_struct.exponent, EXPONENT_LENGTH);
            }
            else
                break;
        }
        left_shift(fraction_sum, shift_bits, FRACTION_LENGTH + 1);            
        for (int i = 0; i < FRACTION_LENGTH + 1; ++i)
            sum_struct.fraction[i] = fraction_sum[i];
    } else {
        sum_struct.sign = a_struct.sign;
        // for the sum with same sign, determine the final exponent and fraction according to the carry out of fraction sum
        if (fraction_sum[FRACTION_LENGTH + 1] == true) {
            sum_struct.exponent = add_one(sum_struct.exponent, EXPONENT_LENGTH);
            for (int i = 0; i < FRACTION_LENGTH + 1; ++i)
                sum_struct.fraction[i] = fraction_sum[i + 1];
        } else {
            for (int i = 0; i < FRACTION_LENGTH + 1; ++i)
                sum_struct.fraction[i] = fraction_sum[i];
        }
    }
    bool * sum = struct_to_bits(sum_struct);
    for (int i = 0; i < 32; ++i)
        out[i] = sum[i];
}

void float_sub(bool * a, bool * b, bool * out) {
    bool * negative_b = (bool *)malloc(sizeof(bool) * 32);
    for (int i = 0; i < 31; ++i)
        negative_b[i] = b[i];
    negative_b[SIGN_POS] = !b[SIGN_POS];
    float_add(a, negative_b, out);
}

void float_mul(bool * a, bool * b, bool * out) {
    // convert bits to IEEE754-format struct
    struct IEEE_format a_struct = bits_to_struct(a);
    struct IEEE_format b_struct = bits_to_struct(b);
    struct IEEE_format product_struct;
    product_struct.fraction = (bool *)malloc(sizeof(bool) * (FRACTION_LENGTH + 1));
    product_struct.exponent = (bool *)malloc(sizeof(bool) * (EXPONENT_LENGTH));
    // compute the sign of the result
    product_struct.sign = a_struct.sign ^ b_struct.sign;
    // multiply the fractions
    bool * fraction_product = mul(a_struct.fraction, b_struct.fraction, FRACTION_LENGTH + 1);
    bool require_shift = false;
    if (fraction_product[2 * FRACTION_LENGTH + 1] == true)
        require_shift = true;
    int offset = 2 * FRACTION_LENGTH + (int)require_shift;
    for (int i = 0; i < FRACTION_LENGTH + 1; ++i)
        product_struct.fraction[FRACTION_LENGTH - i] = fraction_product[offset - i];
    // rounding
    if (fraction_product[offset - FRACTION_LENGTH - 1] == true)
        product_struct.fraction = add_one(product_struct.fraction, FRACTION_LENGTH + 1);
    // add the exponents
    product_struct.exponent = add(a_struct.exponent, b_struct.exponent, EXPONENT_LENGTH, false);
    // remove the duplicated bias
    bool * bias = (bool *)malloc(sizeof(bool) * (EXPONENT_LENGTH));
    for (int i = 0; i < 7; ++i)
        bias[i] = true;
    bias[7] = false;
    product_struct.exponent = sub(product_struct.exponent, bias, EXPONENT_LENGTH);
    // additionally add exponent by 1 if needed
    if (require_shift == true)
        product_struct.exponent = add_one(product_struct.exponent, EXPONENT_LENGTH);
    // convert formatted struct to bits
    bool * product = struct_to_bits(product_struct);
    for (int i = 0; i < 32; ++i) {
        out[i] = product[i];
    }
}

void float_div(bool * a, bool * b, bool * out) {
    // convert bits to IEEE754-format struct
    struct IEEE_format a_struct = bits_to_struct(a);
    struct IEEE_format b_struct = bits_to_struct(b);
    struct IEEE_format div_struct;
    div_struct.fraction = (bool *)malloc(sizeof(bool) * (FRACTION_LENGTH + 1));
    div_struct.exponent = (bool *)malloc(sizeof(bool) * (EXPONENT_LENGTH));
    // compute the sign of the result
    div_struct.sign = a_struct.sign ^ b_struct.sign;
    // subtract the exponents
    div_struct.exponent = sub(a_struct.exponent, b_struct.exponent, EXPONENT_LENGTH);
    // add the bias
    bool * bias = (bool *)malloc(sizeof(bool) * (EXPONENT_LENGTH));
    for (int i = 0; i < 7; ++i)
        bias[i] = true;
    bias[7] = false;
    div_struct.exponent = add(div_struct.exponent, bias, EXPONENT_LENGTH, false);
    // compute the fractions
    bool * fraction_div = divide(a_struct.fraction, b_struct.fraction, FRACTION_LENGTH + 1);
    int shift_bits = 0;
    for (int i = 0; i < FRACTION_LENGTH + 1; ++i) {
        if (fraction_div[FRACTION_LENGTH + 1 - i] == false) {
            shift_bits += 1;
            div_struct.exponent = sub_one(div_struct.exponent, EXPONENT_LENGTH);
        }
        else
            break;
    }
    for (int i = 0; i < FRACTION_LENGTH + 1; ++i)
        div_struct.fraction[FRACTION_LENGTH - i] = fraction_div[FRACTION_LENGTH + 1 - shift_bits - i];
    // rounding
    if ((fraction_div[0] == true) && (shift_bits == 0))
        div_struct.fraction = add_one(div_struct.fraction, FRACTION_LENGTH + 1);
    // convert formatted struct to bits
    bool * product = struct_to_bits(div_struct);
    for (int i = 0; i < 32; ++i) {
        out[i] = product[i];
    }
}
