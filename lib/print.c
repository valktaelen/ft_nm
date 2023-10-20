#include "lib.h"

void	print_number_n_digit(Elf64_Addr n, size_t digit)
{
	static char	*base = "0123456789abcdef";

	while (digit)
		write(1, base + ((n >> (--digit * 4)) % 16), 1);
}

void	print_type(char lower_letter, u_int8_t to_upper)
{
	if (to_upper)
		lower_letter += 'A' - 'a';
	write(1, &lower_letter, 1);
}