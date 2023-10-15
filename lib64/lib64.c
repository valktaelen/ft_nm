#include "lib64.h"

Elf64_Ehdr *get_elf_header(void * const map, const size_t size)
{
	if (size >= sizeof(Elf64_Ehdr))
		return ((Elf64_Ehdr * const) map);
	return (NULL);
}

Elf64_Phdr *get_prg_header(void * const map, const size_t size)
{
	const Elf64_Ehdr * const	elf_header = get_elf_header(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= elf_header->e_phoff + sizeof(Elf64_Phdr))
		return ((Elf64_Phdr * const) map);
	return (NULL);
}

Elf64_Shdr	*get_first_section_header(void * const map, const size_t size)
{
	const Elf64_Ehdr * const	elf_header = get_elf_header(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= elf_header->e_shoff + sizeof(Elf64_Shdr))
		return ((Elf64_Shdr *) map);
	return (NULL);
}

Elf64_Shdr	*get_next_section_header(
	void * const map,
	const size_t size,
	const Elf64_Shdr *current_section_header
)
{
	const void			*end = (void *)current_section_header + sizeof(Elf64_Shdr);
	const void			*new_end = end + sizeof(Elf64_Shdr);

	if (size >= (size_t)(new_end - map))
		return ((Elf64_Shdr *)end);
	return (NULL);
}
