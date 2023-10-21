#ifndef MEMORY_H

# define MEMORY_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <sys/mman.h>

# include "../error/error.h"
# include "../struct.h"

# define FT_LITTLE_ENDIAN 1
# define FT_BIG_ENDIAN 2

# define FT_32 1
# define FT_64 2

size_t		get_file_size(const char *file_path);
t_file		get_file_info(char *prg_name, char *file_path);

// swap bits

u_int8_t	which_endian(void);
uint16_t	swap_uint16(uint16_t val, u_int8_t endian);
uint32_t	swap_uint32(uint32_t val, u_int8_t endian);
uint64_t	swap_uint64(uint64_t val, u_int8_t endian);


#endif
