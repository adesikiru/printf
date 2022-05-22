#include "main.h"

/**
 * set_float_parts - Sets the float_info fields to the appropriate
 * \  parts of a given float
 * @num: The given float
 * @exponent_size: The number of bits in the exponent part
 * @mantissa_size: The number of bits in the mantissa part
 * @float_info: The float_info struct
 */
void set_float_parts(double num, unsigned_char_t exponent_size,
unsigned_char_t mantissa_size, float_info_t *float_info)
{

int i;
char *str;
unsigned_char_t size = exponent_size + mantissa_size + 1;
size_t tmp = *((size_t *)&num);

if (!float_info)
return;
str = malloc(sizeof(char) * (size + 1));
if (str)
{
for (i = 0; i < size; i++)
{
*(str + i) = (tmp % 2)  + '0';
tmp /= 2;
}
*(str + size) = '\0';
rev_string(str);
float_info->sign = *str;
for (i = 0; i < exponent_size; i++)
*(float_info->exponent + i) = *(str + i + 1);
*(float_info->exponent + i) = '\0';
for (i = 0; i < mantissa_size; i++)
*(float_info->mantissa + i) = *(str + i + exponent_size + 1);
*(float_info->mantissa + i) = '\0';
free(str);
}
}

/**
 * mantissa_to_dec_fraction - Converts the mantissa of a float to a fraction
 * @mantissa: The mantissa to convert
 * @frac_len: The maximum length of the decimal fraction
 *
 * Return: The converted fraction
 */
char *mantissa_to_dec_fraction(char *mantissa, unsigned short frac_len)
{
char *str, i, *pow2;
int len = str_len(mantissa);

str = malloc(sizeof(char) * (frac_len + 3));
if (str)
{
mem_set(str, frac_len + 2, '0');
*(str + 1) = '.';
for (i = 0 - 1; i >= 0 - len; i--)
{
if (*(mantissa + ABS(i) - 1) == '1')
{
pow2 = two_exp(i);
str = add_float(pow2, str, TRUE);
}
}
*(str + frac_len + 2) = '\0';
}
return (str);
}

/**
 * float_to_str - Converts a float to its string representation
 * @flt_info: The information about the float
 * @can_free: Specifies whether the given numbers can be freed
 *
 * Return: The string representation of the float, otherwise NULL
 */
char *float_to_str(float_info_t *flt_info, char can_free)
{
unsigned_char_t exponent_size = str_len(flt_info->exponent);
short bias = two_pexp(exponent_size) / 2 - 1, exponent;
char *power, *fraction, *product, *float_num, *hidden_bit, *pow_frac;
short frac_len = 15;/* Only doubles are supported */

hidden_bit = malloc(sizeof(char) * 2);
if (hidden_bit)
{
*(hidden_bit + 0) = '1';
*(hidden_bit + 1) = '\0';
exponent = bin_to_int(flt_info->exponent) - bias;
power = two_exp(exponent);
fraction = mantissa_to_dec_fraction(flt_info->mantissa, frac_len);
fraction = str_cat(hidden_bit, fraction, TRUE);
if (exponent >= 0)
{
pow_frac = malloc(sizeof(char) * 3);
if (pow_frac)
{
*(pow_frac + 0) = '.';
*(pow_frac + 1) = '0';
*(pow_frac + 2) = '\0';
}
power = str_cat(power, pow_frac, TRUE);
}
product = mul_float(fraction, power, TRUE);
float_num = str_cat(flt_info->sign == '1' ? "-" : "", product, FALSE);
free(product);
}
if (can_free)
free_float_info(flt_info);
return (float_num);
}
