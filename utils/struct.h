#ifndef STRUCT_H

# define STRUCT_H

# include <sys/types.h>
# include <elf.h>


/*******************************************/
/**************** 64-bits ******************/
/*******************************************/

typedef struct s_symbol_64
{
	Elf64_Addr			st_value;
	char				type;
	char				*name;
	Elf64_Section		st_shndx;
	u_int8_t			visibility;
	u_int8_t			info_type;
	u_int8_t			bind;
	struct s_symbol_64	*next;
} t_symbol_64;

typedef struct s_Sym_64
{
	Elf64_Word		st_name;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf64_Section	st_shndx;
	Elf64_Addr		st_value;
	Elf64_Xword		st_size;
	u_int8_t		visibility;
	u_int8_t		type;
	u_int8_t		bind;
} t_Sym_64;

typedef struct s_S_hdr_64
{
	Elf64_Word	sh_name;
	Elf64_Word	sh_type;
	Elf64_Xword	sh_flags;
	Elf64_Off	sh_offset;
	Elf64_Xword	sh_size;
	Elf64_Word	sh_link;
	Elf64_Word	sh_info;
	Elf64_Xword	sh_entsize;
} t_S_hdr_64;

typedef struct s_binary_64 {
	Elf64_Off	e_shoff;
	Elf64_Half	e_shentsize;
	Elf64_Half	e_shnum;
	Elf64_Half	e_shstrndx;
	Elf64_Shdr	*hdrs;
	t_symbol_64	*syms;
}	t_binary_64;


/*******************************************/
/**************** 32-bits ******************/
/*******************************************/

typedef struct s_symbol_32
{
	Elf32_Addr			st_value;
	char				type;
	char				*name;
	Elf32_Section		st_shndx;
	u_int8_t			visibility;
	u_int8_t			info_type;
	u_int8_t			bind;
	struct s_symbol_32	*next;
} t_symbol_32;

typedef struct s_Sym_32
{
	Elf32_Word		st_name;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf32_Section	st_shndx;
	Elf32_Addr		st_value;
	Elf32_Word		st_size;
	u_int8_t		visibility;
	u_int8_t		type;
	u_int8_t		bind;
} t_Sym_32;

typedef struct s_S_hdr_32
{
	Elf32_Word	sh_name;
	Elf32_Word	sh_type;
	Elf32_Word	sh_flags;
	Elf32_Off	sh_offset;
	Elf32_Word	sh_size;
	Elf32_Word	sh_link;
	Elf32_Word	sh_info;
	Elf32_Word	sh_entsize;
} t_S_hdr_32;

typedef struct s_binary_32 {
	Elf32_Off	e_shoff;
	Elf32_Half	e_shentsize;
	Elf32_Half	e_shnum;
	Elf32_Half	e_shstrndx;
	Elf32_Shdr	*hdrs;
	t_symbol_32	*syms;
}	t_binary_32;


/*******************************************/
/**************** General ******************/
/*******************************************/

typedef struct s_global_infos
{
	u_int8_t	arch;
	u_int8_t	endian;
	void		*map;
}	t_global_infos;



typedef struct s_nm
{
	char *		prg_name;
	char *		file_path;
	size_t		file_size;
	int			fd;
	t_global_infos	global_infos;
	t_binary_32	bin_32;
	t_binary_64	bin_64;
}	t_nm;

#endif
