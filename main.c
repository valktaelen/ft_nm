#include "header.h"

// u_int8_t	ft_nm_32_old(t_binary_32 *bin)
// {
// 	Elf32_Shdr	*section_hdr;
// 	Elf32_Word	type;
// 	Elf32_Word	size;
// 	Elf32_Off	offset;
// 	Elf32_Half	i;
// 	u_int8_t	pass;

// 	pass = 1;
// 	i = 0;
// 	while (i < swap_uint16(bin->elf_hdr->e_shnum, bin->endian))
// 	{
// 		section_hdr = get_n_section_header_32(bin, i);
// 		type = swap_uint32(section_hdr->sh_type, bin->endian);
// 		if (type == SHT_SYMTAB || type == SHT_SYMTAB_SHNDX)
// 		{
// 			offset = swap_uint32(section_hdr->sh_offset, bin->endian);
// 			size = swap_uint32(section_hdr->sh_size, bin->endian);
// 			Elf32_Sym	*sym = bin->file.map + offset;
// 			while ((void *)sym < bin->file.map + offset + size)
// 			{
// 				Elf32_Shdr	*str_section_hdr = get_n_section_header_32(bin, swap_uint32(section_hdr->sh_link, bin->endian));
// 				if (pass)
// 					pass = 0;
// 				else
// 					print_sym_32(sym, bin->file.map + swap_uint32(str_section_hdr->sh_offset, bin->endian), bin);
// 				sym = (void *)sym + swap_uint32(section_hdr->sh_entsize, bin->endian);
// 			}
// 		}
// 		++i;
// 	}
// 	return (0);
// }

// u_int8_t	ft_nm_64_old(t_binary_64 *bin)
// {
// 	Elf64_Shdr	*section_hdr;
// 	Elf64_Word	type;
// 	Elf64_Word	size;
// 	Elf64_Off	offset;
// 	Elf64_Half	i;
// 	u_int8_t	pass;

// 	i = 0;
// 	pass = 1;
// 	while (i < swap_uint16(bin->elf_hdr->e_shnum, bin->endian))
// 	{
// 		section_hdr = get_n_section_header_64(bin, i);
// 		type = swap_uint32(section_hdr->sh_type, bin->endian);
// 		if (type == SHT_SYMTAB || type == SHT_SYMTAB_SHNDX)
// 		{
// 			offset = swap_uint64(section_hdr->sh_offset, bin->endian);
// 			size = swap_uint64(section_hdr->sh_size, bin->endian);
// 			Elf64_Sym	*sym = bin->file.map + offset;
// 			while ((void *)sym < bin->file.map + offset + size)
// 			{
// 				Elf64_Shdr	*str_section_hdr = get_n_section_header_64(bin, swap_uint32(section_hdr->sh_link, bin->endian));
// 				if (pass)
// 					pass = 0;
// 				else
// 					print_sym_64(sym, bin->file.map + swap_uint64(str_section_hdr->sh_offset, bin->endian), bin);
// 				sym = (void *)sym + swap_uint64(section_hdr->sh_entsize, bin->endian);
// 			}
// 		}
// 		++i;
// 	}
// 	return (0);
// }




// int	ft_nm_32(t_nm *nm)
// {
// 	return (0);
// }


// void	ft_print_32(t_nm *nm, int index)
// {

// }

void	ft_clean_nm(t_nm *nm)
{
	nm->fd = -1;
	nm->file_size = 0;
	nm->global_infos.arch = 0;
	nm->global_infos.endian = 0;
	nm->bin_64.e_shentsize = 0;
	nm->bin_64.e_shnum = 0;
	nm->bin_64.e_shoff = 0;
	nm->bin_64.e_shstrndx = 0;
	nm->bin_64.hdrs = NULL;
	if (nm->bin_64.syms)
		ft_clean_nm_64(nm->bin_64.syms);
	nm->bin_64.syms = NULL;
	nm->bin_32.e_shentsize = 0;
	nm->bin_32.e_shnum = 0;
	nm->bin_32.e_shoff = 0;
	nm->bin_32.e_shstrndx = 0;
	nm->bin_32.hdrs = NULL;
	if (nm->bin_32.syms)
		ft_clean_nm_32(nm->bin_32.syms);
	nm->bin_32.syms = NULL;
}

int	ft_nm(t_nm *nm, int index)
{
	int	ret;

	ft_clean_nm(nm);
	ret = 0;
	if (ft_check_file(nm) || ft_get_fd(nm))
		return (1);
	ret = ft_get_global_infos(nm);
	close(nm->fd);
	if (ret)
		return (1);
	if (nm->global_infos.arch == FT_64)
	{
		ret = ft_nm_64(nm);
		if (!ret)
			ft_print_64(nm, index);
	}
	else
	{
		ret = ft_nm_32(nm);
		if (!ret)
			ft_print_32(nm, index);
	}
	munmap(nm->global_infos.map, nm->file_size);
	return (ret);
}

int main(const int argc, char *argv[])
{
	t_nm		nm;
	int			i;
	int			ret;

	nm.prg_name = argv[0];
	nm.bin_64.syms = NULL;
	nm.bin_32.syms = NULL;
	if (argc == 1)
	{
		nm.file_path = DEFAULT_PRG;
		ret = ft_nm(&nm, 0);
	}
	else
	{
		i = 0;
		while (i < argc - 1)
		{
			nm.file_path = argv[i + 1];
			if (ft_nm(&nm, i + 1 - (argc == 2)))
				ret = 1;
			++i;
		}
	}
	ft_clean_nm(&nm);
	return (ret);
}
