#include "lib.h"


Elf64_Ehdr *get_elf_header_64(void * const map, const size_t size)
{
	Elf64_Ehdr * const	elf_header = map;

	if (size >= sizeof(Elf64_Ehdr) && size >= swap_uint16(elf_header->e_ehsize, elf_header->e_ident[EI_DATA]))
		if (elf_header->e_ident[EI_MAG0] == ELFMAG0
			&& elf_header->e_ident[EI_MAG1] == ELFMAG1
			&& elf_header->e_ident[EI_MAG2] == ELFMAG2
			&& elf_header->e_ident[EI_MAG3] == ELFMAG3)
			return (elf_header);
	return (NULL);
}

Elf64_Phdr	*get_prg_header_64(void * const map, const size_t size, const u_int8_t endian)
{
	Elf64_Ehdr * const	elf_header = get_elf_header_64(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= swap_uint64(elf_header->e_phoff, endian) + swap_uint16(elf_header->e_phentsize, endian))
		return (map + swap_uint64(elf_header->e_phoff, endian));
	return (NULL);
}

Elf64_Shdr	*get_first_section_header_64(void * const map, const size_t size, const u_int8_t endian)
{
	Elf64_Ehdr * const	elf_header = get_elf_header_64(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= swap_uint64(elf_header->e_shoff, endian) + swap_uint16(elf_header->e_shentsize, endian))
		return (map + swap_uint64(elf_header->e_shoff, endian));
	return (NULL);
}

Elf64_Shdr	*get_next_section_header_64(
	void * const map,
	const size_t size,
	const Elf64_Shdr *current_section_header,
	const u_int8_t endian
)
{
	const Elf64_Ehdr * const	elf_header = get_elf_header_64(map, size);
	const void			*end = (void *)current_section_header + swap_uint16(elf_header->e_shentsize, endian);
	const void			*new_end = end + swap_uint16(elf_header->e_shentsize, endian);

	if (size >= (size_t)(new_end - map))
		return ((Elf64_Shdr *)end);
	return (NULL);
}

Elf64_Shdr	*get_n_section_header_64(
	t_binary_64 *bin,
	size_t n
)
{
	const void			*end = ((void *)bin->fst_sec_hdr) + swap_uint16(bin->elf_hdr->e_shentsize, bin->endian) * n;
	const void			*new_end = end + swap_uint16(bin->elf_hdr->e_shentsize, bin->endian);

	if (bin->file.size >= (size_t)(new_end - bin->file.map))
		return ((Elf64_Shdr *)end);
	return (NULL);
}
#include <stdio.h>
u_int8_t	get_binary_64(t_binary_64 *bin)
{
	Elf64_Shdr	*section_hdr;

	bin->elf_hdr = get_elf_header_64(bin->file.map, bin->file.size);
	bin->endian = bin->elf_hdr->e_ident[EI_DATA];
	bin->prg_hdr = get_prg_header_64(bin->file.map, bin->file.size, bin->endian);
	bin->fst_sec_hdr = get_first_section_header_64(bin->file.map, bin->file.size, bin->endian);
	section_hdr = get_n_section_header_64(bin, swap_uint16(bin->elf_hdr->e_shstrndx, bin->endian));
	if (!bin->elf_hdr || !bin->prg_hdr || !bin->fst_sec_hdr || !section_hdr
		|| swap_uint64(section_hdr->sh_offset, bin->endian) >= bin->file.size)
		return (1);
	bin->shstrtab = bin->file.map + swap_uint64(section_hdr->sh_offset, bin->endian);
	return (0);
}
