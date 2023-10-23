#include "../lib.h"

int	ft_nm_symbol_32(t_nm *nm, const t_S_hdr_32 *hdr, Elf32_Sym *map_sym)
{
	const t_Sym_32	*sym = ft_get_symbol_32(nm, map_sym);
	t_symbol_32		*node_sym;
	char			*name;

	if (!sym)
		return (1);
	name = ft_symbol_get_name_32(nm, hdr, sym);
	if (!name)
		return (1);
	node_sym = malloc(sizeof(t_symbol_32));
	if (!node_sym)
	{
		print_prg_error(nm, ERR_MALLOC);
		free(name);
		free((void *)sym);
		return (1);
	}
	node_sym->st_value = sym->st_value;
	node_sym->name = name;
	node_sym->st_shndx = sym->st_shndx;
	node_sym->visibility = sym->visibility;
	node_sym->info_type = sym->type;
	node_sym->bind = sym->bind;
	node_sym->type = ft_symbol_get_type_32(nm, sym, name);
	ft_list_sym_add_32(nm, node_sym);
	free((void *)sym);
	return (0);
}

int	ft_nm_section_32(t_nm *nm, const Elf32_Shdr *hdr)
{
	const t_S_hdr_32	*s_hdr = ft_get_section_32(nm, (Elf32_Shdr *)hdr);
	Elf32_Sym			*symbols;
	Elf32_Xword			offset;

	if (!s_hdr)
		return (1);
	if (s_hdr->sh_type == SHT_SYMTAB || s_hdr->sh_type == SHT_SYMTAB_SHNDX)
	{
		symbols = ft_get_section_content_32(nm, (Elf32_Shdr *)hdr);
		if (!symbols)
		{
			print_prg_error(nm, ERR_FILE_RECONIZED);
			free((void *)s_hdr);
			return (1);
		}
		offset = 0;
		while (offset < s_hdr->sh_size)
		{
			if (ft_nm_symbol_32(nm, s_hdr, (void *)symbols + offset))
				break ;
			offset += s_hdr->sh_entsize;
		}
	}
	free((void *)s_hdr);
	return (0);
}

int	ft_nm_32(t_nm *nm)
{
	Elf32_Half	i_section;
	Elf32_Shdr	*section;

	if (ft_get_elf_hdr_infos_32(nm))
		return (1);
	i_section = 0;
	while (i_section < nm->bin_32.e_shnum)
	{
		section = ft_get_section_hdr_32(nm, i_section);
		if (!section || ft_nm_section_32(nm, section))
		{
			nm->bin_32.hdrs = NULL;
			return (1);
		}
		++i_section;
	}
	nm->bin_32.hdrs = NULL;
	return (0);
}
