#ifndef LIB64_H

# define LIB64_H
# include <elf.h>
# include <sys/types.h>
# include <stdlib.h>

# include "../error/error.h"


Elf64_Ehdr *get_elf_header(
	void * const map,
	const size_t size
);
Elf64_Phdr *get_prg_header(
	void * const map,
	const size_t size
);
Elf64_Shdr	*get_first_section_header(
	void * const map,
	const size_t size
);
Elf64_Shdr	*get_next_section_header(
	void * const map,
	const size_t size,
	const Elf64_Shdr *current_section_header
);


void	print_elf_header_64(Elf64_Ehdr *hdr);
void	print_prg_header_64(Elf64_Phdr *hdr);
void	print_section_header_64(Elf64_Shdr *hdr, char *shstrtab);
void	print_sym_64(Elf64_Sym *sym, char *str_tab);

#endif
