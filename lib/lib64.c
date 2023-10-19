#include "lib.h"


Elf64_Ehdr *get_elf_header_64(void * const map, const size_t size)
{
	Elf64_Ehdr * const	elf_header = map;

	if (size >= sizeof(Elf64_Ehdr) && size >= elf_header->e_ehsize)
		return (elf_header);
	return (NULL);
}

Elf64_Phdr	*get_prg_header_64(void * const map, const size_t size)
{
	Elf64_Ehdr * const	elf_header = get_elf_header_64(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= elf_header->e_phoff + elf_header->e_phentsize)
		return (map + elf_header->e_phoff);
	return (NULL);
}

Elf64_Shdr	*get_first_section_header_64(void * const map, const size_t size)
{
	Elf64_Ehdr * const	elf_header = get_elf_header_64(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= elf_header->e_shoff + elf_header->e_shentsize)
		return (map + elf_header->e_shoff);
	return (NULL);
}

Elf64_Shdr	*get_next_section_header_64(
	void * const map,
	const size_t size,
	const Elf64_Shdr *current_section_header
)
{
	const Elf64_Ehdr * const	elf_header = get_elf_header_64(map, size);
	const void			*end = (void *)current_section_header + elf_header->e_shentsize;
	const void			*new_end = end + elf_header->e_shentsize;

	if (size >= (size_t)(new_end - map))
		return ((Elf64_Shdr *)end);
	return (NULL);
}

Elf64_Shdr	*get_n_section_header_64(
	t_binary_64 *bin,
	size_t n
)
{
	const void			*end = ((void *)bin->fst_sec_hdr) + bin->elf_hdr->e_shentsize * n;
	const void			*new_end = end + bin->elf_hdr->e_shentsize;

	if (bin->file.size >= (size_t)(new_end - bin->file.map))
		return ((Elf64_Shdr *)end);
	return (NULL);
}

u_int8_t	get_binary_64(t_binary_64 *bin)
{
	Elf64_Shdr	*section_hdr;

	bin->elf_hdr = get_elf_header_64(bin->file.map, bin->file.size);
	bin->prg_hdr = get_prg_header_64(bin->file.map, bin->file.size);
	bin->fst_sec_hdr = get_first_section_header_64(bin->file.map, bin->file.size);
	section_hdr = get_n_section_header_64(bin, bin->elf_hdr->e_shstrndx);
	if (!bin->elf_hdr || !bin->prg_hdr || !bin->fst_sec_hdr || !section_hdr
		|| section_hdr->sh_offset >= bin->file.size)
		return (1);
	bin->shstrtab = bin->file.map + section_hdr->sh_offset;
	return (0);
}
