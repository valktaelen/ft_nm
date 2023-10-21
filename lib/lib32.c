#include "lib.h"


Elf32_Ehdr *get_elf_header_32(void * const map, const size_t size)
{
	Elf32_Ehdr * const	elf_header = map;

	if (size >= sizeof(Elf32_Ehdr) && size >= swap_uint16(elf_header->e_ehsize, elf_header->e_ident[EI_DATA]))
		return (elf_header);
	return (NULL);
}

Elf32_Phdr	*get_prg_header_32(void * const map, const size_t size, const u_int8_t endian)
{
	Elf32_Ehdr * const	elf_header = get_elf_header_32(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= swap_uint32(elf_header->e_phoff, endian) + swap_uint16(elf_header->e_phentsize, endian))
		return (map + swap_uint32(elf_header->e_phoff, endian));
	return (NULL);
}

Elf32_Shdr	*get_first_section_header_32(void * const map, const size_t size, const u_int8_t endian)
{
	Elf32_Ehdr * const	elf_header = get_elf_header_32(map, size);

	if (!elf_header)
		return (NULL);
	if (size >= swap_uint32(elf_header->e_shoff, endian) + swap_uint16(elf_header->e_shentsize, endian))
		return (map + swap_uint32(elf_header->e_shoff, endian));
	return (NULL);
}

Elf32_Shdr	*get_next_section_header_32(
	void * const map,
	const size_t size,
	const Elf32_Shdr *current_section_header,
	const u_int8_t endian
)
{
	const Elf32_Ehdr * const	elf_header = get_elf_header_32(map, size);
	const void			*end = (void *)current_section_header + swap_uint16(elf_header->e_shentsize, endian);
	const void			*new_end = end + swap_uint16(elf_header->e_shentsize, endian);

	if (size >= (size_t)(new_end - map))
		return ((Elf32_Shdr *)end);
	return (NULL);
}

Elf32_Shdr	*get_n_section_header_32(
	t_binary_32 *bin,
	size_t n
)
{
	const void			*end = ((void *)bin->fst_sec_hdr) + swap_uint16(bin->elf_hdr->e_shentsize, bin->endian) * n;
	const void			*new_end = end + swap_uint16(bin->elf_hdr->e_shentsize, bin->endian);

	if (bin->file.size >= (size_t)(new_end - bin->file.map))
		return ((Elf32_Shdr *)end);
	return (NULL);
}
#include <stdio.h>
u_int8_t	get_binary_32(t_binary_32 *bin)
{
	Elf32_Shdr	*section_hdr;

	bin->elf_hdr = get_elf_header_32(bin->file.map, bin->file.size);
	bin->endian = bin->elf_hdr->e_ident[EI_DATA];
	bin->prg_hdr = get_prg_header_32(bin->file.map, bin->file.size, bin->endian);
	bin->fst_sec_hdr = get_first_section_header_32(bin->file.map, bin->file.size, bin->endian);
	section_hdr = get_n_section_header_32(bin, swap_uint16(bin->elf_hdr->e_shstrndx, bin->endian));
	if (!bin->elf_hdr || !bin->prg_hdr || !bin->fst_sec_hdr || !section_hdr
		|| swap_uint32(section_hdr->sh_offset, bin->endian) >= bin->file.size)
		return (1);
	bin->shstrtab = bin->file.map + swap_uint32(section_hdr->sh_offset, bin->endian);
	return (0);
}
