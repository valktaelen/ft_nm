#ifndef LIB64_H

# define LIB64_H
# include <elf.h>
# include <sys/types.h>
# include <stdlib.h>


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

#endif
