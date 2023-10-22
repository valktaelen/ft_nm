#include "header.h"

#define DEFAULT_PRG "a.out"

u_int8_t	ft_nm_32(t_binary_32 *bin)
{
	Elf32_Shdr	*section_hdr;
	Elf32_Word	type;
	Elf32_Word	size;
	Elf32_Off	offset;
	Elf32_Half	i;
	u_int8_t	pass;

	pass = 1;
	i = 0;
	while (i < swap_uint16(bin->elf_hdr->e_shnum, bin->endian))
	{
		section_hdr = get_n_section_header_32(bin, i);
		type = swap_uint32(section_hdr->sh_type, bin->endian);
		if (type == SHT_SYMTAB || type == SHT_SYMTAB_SHNDX)
		{
			offset = swap_uint32(section_hdr->sh_offset, bin->endian);
			size = swap_uint32(section_hdr->sh_size, bin->endian);
			Elf32_Sym	*sym = bin->file.map + offset;
			while ((void *)sym < bin->file.map + offset + size)
			{
				Elf32_Shdr	*str_section_hdr = get_n_section_header_32(bin, swap_uint32(section_hdr->sh_link, bin->endian));
				if (pass)
					pass = 0;
				else
					print_sym_32(sym, bin->file.map + swap_uint32(str_section_hdr->sh_offset, bin->endian), bin);
				sym = (void *)sym + swap_uint32(section_hdr->sh_entsize, bin->endian);
			}
		}
		++i;
	}
	return (0);
}

u_int8_t	ft_nm_64(t_binary_64 *bin)
{
	Elf64_Shdr	*section_hdr;
	Elf64_Word	type;
	Elf64_Word	size;
	Elf64_Off	offset;
	Elf64_Half	i;
	u_int8_t	pass;

	i = 0;
	pass = 1;
	while (i < swap_uint16(bin->elf_hdr->e_shnum, bin->endian))
	{
		section_hdr = get_n_section_header_64(bin, i);
		type = swap_uint32(section_hdr->sh_type, bin->endian);
		if (type == SHT_SYMTAB || type == SHT_SYMTAB_SHNDX)
		{
			offset = swap_uint64(section_hdr->sh_offset, bin->endian);
			size = swap_uint64(section_hdr->sh_size, bin->endian);
			Elf64_Sym	*sym = bin->file.map + offset;
			while ((void *)sym < bin->file.map + offset + size)
			{
				Elf64_Shdr	*str_section_hdr = get_n_section_header_64(bin, swap_uint32(section_hdr->sh_link, bin->endian));
				if (pass)
					pass = 0;
				else
					print_sym_64(sym, bin->file.map + swap_uint64(str_section_hdr->sh_offset, bin->endian), bin);
				sym = (void *)sym + swap_uint64(section_hdr->sh_entsize, bin->endian);
			}
		}
		++i;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	int			i;
	char		*prg;
	t_binary_64	bin;

	i = 0;
	while (i < argc - 1 + (argc == 1))
	{
		if (argc == 1)
			prg = DEFAULT_PRG;
		else
			prg = argv[i + 1];
		bin.file = get_file_info(argv[0], prg);
		if (!bin.file.map || !bin.file.size)
		{
			++i;
			continue ;
		}
		Elf32_Ehdr	*elf_hdr = get_elf_header_32(bin.file.map, bin.file.size);
		if (!elf_hdr)
		{
			print_prg_error_file(&bin.file, ERR_FILE, 0);
			munmap(bin.file.map, bin.file.size);
			++i;
			continue ;
		}
		//print_elf_header_32(elf_hdr);
		if (elf_hdr->e_ident[EI_CLASS] == FT_64)
		{
			if (get_binary_64(&bin))
			{
				print_prg_error_file(&bin.file, ERR_FILE, 0);
				munmap(bin.file.map, bin.file.size);
				++i;
				continue ;
			}
			ft_nm_64(&bin);
		}
		else
		{
			if (get_binary_32((t_binary_32 *)&bin))
			{
				print_prg_error_file(&bin.file, ERR_FILE, 0);
				munmap(bin.file.map, bin.file.size);
				++i;
				continue ;
			}
			ft_nm_32((t_binary_32 *)&bin);
		}
		munmap(bin.file.map, bin.file.size);
		++i;
	}
	return 0;
}
