#ifndef STRUCT_H

# define STRUCT_H

# include <sys/types.h>
# include <elf.h>

typedef struct s_file
{
	char *	prg_name;
	char *	file_path;
	void *	map;
	size_t	size;
}	t_file;

typedef struct s_binary_64 {
	t_file		file;
	Elf64_Ehdr	*elf_hdr;
	Elf64_Phdr	*prg_hdr;
	Elf64_Shdr	*fst_sec_hdr;
	char		*shstrtab;
	u_int8_t	endian;
}	t_binary_64;

typedef struct s_binary_32 {
	t_file		file;
	Elf32_Ehdr	*elf_hdr;
	Elf32_Phdr	*prg_hdr;
	Elf32_Shdr	*fst_sec_hdr;
	char		*shstrtab;
	u_int8_t	endian;
}	t_binary_32;

#endif
