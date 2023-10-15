#ifndef MEMORY_H

# define MEMORY_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <sys/mman.h>

# include "../error/error.h"
# include "../struct.h"


size_t	get_file_size(const char *file_path);
t_file	get_file_info(char *prg_name, char *file_path);

#endif
