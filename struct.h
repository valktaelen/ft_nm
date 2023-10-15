#ifndef STRUCT_H

# define STRUCT_H

# include <sys/types.h>

typedef struct s_file
{
	char *	prg_name;
	void *	map;
	int		prg_fd;
	size_t	size;
}	t_file;

#endif
