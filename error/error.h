#ifndef ERROR_H

# define ERROR_H

# include <errno.h>
# include <unistd.h>
# include <string.h>

# define SEP_1 ": "
# define SEP_SPACE " "
# define SEP_NL "\n"

# include "../struct.h"

size_t	ft_strlen(const char *str);
void	print_prg_error_file(t_file *file, char *error, u_int8_t is_errno);
void	print_prg_error(char *file_path, char *error, u_int8_t is_errno);

#endif
