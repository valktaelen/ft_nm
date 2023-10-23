#ifndef UTILS_H

# define UTILS_H

/**************************************/
/************  INCLUDES  **************/
/**************************************/

// errno
# include "errno.h"
// stat
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
// open
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
// mmap
# include <sys/mman.h>
// write
# include <unistd.h>
// malloc free
# include <stdlib.h>

# include "struct.h"

// TODO rm
#include <stdio.h>
#include <string.h>

/**************************************/
/*************  DEFINES  **************/
/**************************************/

// writes
# define SEP_1		": "
# define SEP_SPACE	" "
# define SEP_NL		"\n"

// constants
# define DEFAULT_PRG		"a.out"
# define DEBUG_SECTION		".debug"

# define FT_LITTLE_ENDIAN	1
# define FT_BIG_ENDIAN		2

# define FT_32 1
# define FT_64 2

// errors
# define ERR_FILE_RECONIZED		"file format not reconized"
# define ERR_FILE_ACCESS		"permission denied"
# define ERR_FILE_MANY_SYM		"too many symbolic links encountered"
# define ERR_FILE_PATH_LONG		"pathname is too long"
# define ERR_FILE_PATH_EMPTY	"pathname is an empty string"
# define ERR_FILE_NO_EXIST		"No such file"

# define ERR_FILE_OPEN			"Can't open file"

# define ERR_MAP_FAIL			"map failed"
# define ERR_MALLOC				"malloc failed"

# define INFO_NO_SYM			"No symbols"


/**************************************/
/***********  PROTOTYPES  *************/
/**************************************/

// tools
size_t	ft_strlen(char * str);
int	ft_strncmp(char *s1, char *s2, const size_t n);
void	print_prg_error(t_nm *nm, char *error);
char	*ft_strdup(char *str);
void	print_number_n_digit(Elf64_Addr n, size_t digit);
char	get_char_lower_upper(char lower_letter, u_int8_t to_upper);

// file
int		ft_check_file(t_nm *nm);
int		ft_get_fd(t_nm *nm);

// memory
void	*ft_get_map(t_nm *nm, size_t len, off_t offset);

// swap bits
u_int8_t	which_endian(void);
uint16_t	swap_uint16(uint16_t val, u_int8_t endian);
uint32_t	swap_uint32(uint32_t val, u_int8_t endian);
uint64_t	swap_uint64(uint64_t val, u_int8_t endian);

#endif
