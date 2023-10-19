#ifndef STRUCT_H

# define STRUCT_H

# include <sys/types.h>
# include <elf.h>

typedef struct s_file
{
	char *	prg_name;
	void *	map;
	size_t	size;
}	t_file;

typedef struct s_binary_64 {
	t_file		file;
	Elf64_Ehdr	*elf_hdr;
	Elf64_Phdr	*prg_hdr;
	Elf64_Shdr	*fst_sec_hdr;
	char		*shstrtab;
}	t_binary_64;

#endif
