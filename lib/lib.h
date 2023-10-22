#ifndef LIB64_H

# define LIB64_H
# include <elf.h>
# include <sys/types.h>
# include <stdlib.h>

# include "../error/error.h"
# include "../memory/memory.h"

# define DEBUG_SECTION	".debug"
# define MAGIC			((const unsigned char *)"\x7F\x45\x4C\x46")

// 64-bits

Elf64_Ehdr	*get_elf_header_64(
	void * const map,
	const size_t size
);
Elf64_Phdr	*get_prg_header_64(
	void * const map,
	const size_t size,
	u_int8_t endian
);
Elf64_Shdr	*get_first_section_header_64(
	void * const map,
	const size_t size,
	u_int8_t endian
);
Elf64_Shdr	*get_next_section_header_64(
	void * const map,
	const size_t size,
	const Elf64_Shdr *current_section_header,
	u_int8_t endian
);

Elf64_Shdr	*get_n_section_header_64(
	t_binary_64 *bin,
	size_t n
);

u_int8_t	get_binary_64(t_binary_64 *bin);


// 32-bits

Elf32_Ehdr *get_elf_header_32(void * const map, const size_t size);
Elf32_Phdr	*get_prg_header_32(void * const map, const size_t size, u_int8_t endian);
Elf32_Shdr	*get_first_section_header_32(void * const map, const size_t size, u_int8_t endian);
Elf32_Shdr	*get_next_section_header_32(
	void * const map,
	const size_t size,
	const Elf32_Shdr *current_section_header,
	u_int8_t endian
);
Elf32_Shdr	*get_n_section_header_32(
	t_binary_32 *bin,
	size_t n
);
u_int8_t	get_binary_32(t_binary_32 *bin);

// print

void	print_number_n_digit(Elf64_Addr n, size_t digit);
char	print_type(char lower_letter, u_int8_t to_upper);

void	print_elf_header_64(Elf64_Ehdr *hdr);
void	print_prg_header_64(Elf64_Phdr *hdr);
void	print_section_header_64(Elf64_Shdr *hdr, char *shstrtab);
void	print_sym_64(Elf64_Sym *sym, char *str_tab, t_binary_64 *bin);
void	print_elf_header_32(Elf32_Ehdr *hdr);
void	print_prg_header_32(Elf32_Phdr *hdr, u_int8_t endian);
void	print_section_header_32(Elf32_Shdr *hdr, char *shstrtab, u_int8_t endian);
void	print_sym_32(Elf32_Sym *sym, char *str_tab, t_binary_32 *bin);

#endif
