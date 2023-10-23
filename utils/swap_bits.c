#include "utils.h"

u_int8_t	which_endian(void)
{
	unsigned int i = 1;
	char *c = (char*)&i;
	if (*c)
		return FT_LITTLE_ENDIAN;
	return FT_BIG_ENDIAN;
}

uint16_t	swap_uint16(uint16_t val, u_int8_t endian)
{
	if (endian == which_endian())
		return (val);
	return ((val << 8) | (val >> 8 ));
}

uint32_t	swap_uint32(uint32_t val, u_int8_t endian)
{
	if (endian == which_endian())
		return (val);
	val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
	return ((val << 16) | (val >> 16));
}
uint64_t	swap_uint64(uint64_t val, u_int8_t endian)
{
	if (endian == which_endian())
		return (val);
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
	return ((val << 32) | (val >> 32));
}
