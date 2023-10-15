#ifndef HEADER_H
# define HEADER_H

/****************************************************/
/***************    System headers    ***************/
/****************************************************/

//// Authorized functions

// 2 open - 2 fstat
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

// 2 close - 2 write
# include <unistd.h>

// 2 mmap - 2 munmap
# include <sys/mman.h>

// 3 malloc - 3 free
# include <stdlib.h>

//// Plus

# include <elf.h>


#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "error/error.h"
#include "memory/memory.h"
#include "lib64/lib64.h"

/****************************************************/
/***************       Defines        ***************/
/****************************************************/


/****************************************************/
/***************      Structures      ***************/
/****************************************************/

typedef struct s_lib
{
	uint8_t	arch;
	void	(*get_header_elf)(void * map);
	void	(*get_header_prg)(void *map, void *header);
}	t_lib;

typedef struct s_nm
{
	const char * const	prg_name;
	const int			prg_fd;
	t_lib * const		lib;
	void				*header_elf;
	void				*header_prg;
}	t_nm;

/****************************************************/
/***************      Prototypes      ***************/
/****************************************************/


#endif
