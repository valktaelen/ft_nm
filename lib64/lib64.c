#include "lib64.h"

Elf64_Ehdr *get_elf_header(void * const map, const size_t size)
{
	const Elf64_Ehdr * const	elf_header = map;

	if (size >= elf_header->e_ehsize)
		return (elf_header);
	return (NULL);
}

Elf64_Phdr *get_prg_header(void * const map, const size_t size)
{
	const Elf64_Ehdr * const	elf_header = get_elf_header(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= elf_header->e_phoff + elf_header->e_phentsize)
		return ((Elf64_Phdr * const) map);
	return (NULL);
}

Elf64_Shdr	*get_first_section_header(void * const map, const size_t size)
{
	const Elf64_Ehdr * const	elf_header = get_elf_header(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= elf_header->e_shoff + elf_header->e_shentsize)
		return ((Elf64_Shdr *) (map + elf_header->e_shoff));
	return (NULL);
}

Elf64_Shdr	*get_next_section_header(
	void * const map,
	const size_t size,
	const Elf64_Shdr *current_section_header
)
{
	const Elf64_Ehdr * const	elf_header = get_elf_header(map, size);
	const void			*end = (void *)current_section_header + elf_header->e_shentsize;
	const void			*new_end = end + elf_header->e_shentsize;

	if (size >= (size_t)(new_end - map))
		return ((Elf64_Shdr *)end);
	return (NULL);
}
