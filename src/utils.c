#include "utils.h"

int compare_string(const char *s1, const char *s2){
	if (s1 == NULL || s2 == NULL)
		return -1;
	while (*s1 && *s2 && *s1 == *s2)
		s1++;
	return *s1 - *s2;
}

double possible_codes(const double number_of_colors, const double code_length)
/* returns the possible number of combinations */
{
    double c = pow(number_of_colors, code_length);
    return c;
}
