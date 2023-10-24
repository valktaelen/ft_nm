/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:01 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 06:35:53 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

t_Sym_32	*ft_get_symbol_32(t_nm *nm, Elf32_Sym *map_sym)
{
	const u_int8_t	endian = nm->global_infos.endian;
	t_Sym_32		*sym;

	sym = malloc(sizeof(t_Sym_32));
	if (!sym)
	{
		print_prg_error(nm, ERR_MALLOC);
		return (NULL);
	}
	sym->st_name = swap_uint32(map_sym->st_name, endian);
	sym->st_info = map_sym->st_info;
	sym->st_other = map_sym->st_other;
	sym->st_shndx = swap_uint16(map_sym->st_shndx, endian);
	sym->st_value = swap_uint32(map_sym->st_value, endian);
	sym->st_size = swap_uint32(map_sym->st_size, endian);
	sym->visibility = ELF32_ST_VISIBILITY(sym->st_other);
	sym->type = ELF32_ST_TYPE(sym->st_info);
	sym->bind = ELF32_ST_BIND(sym->st_info);
	return (sym);
}

static char	*ft_symbol_get_name_section_32(t_nm *nm,
	const t_Sym_32 *sym,
	char *str_tab)
{
	Elf32_Shdr	*sh_link_sym;

	sh_link_sym = ft_get_section_hdr_32(nm, sym->st_shndx);
	if (!sh_link_sym)
		return (NULL);
	return (
		str_tab + swap_uint32(sh_link_sym->sh_name, nm->global_infos.endian)
	);
}

char	*ft_symbol_get_name_32(t_nm *nm, const t_S_hdr_32 *hdr,
	const t_Sym_32 *sym)
{
	Elf32_Shdr	*sh_link;
	char		*str_tab;

	if (sym->type == STT_SECTION)
		sh_link = ft_get_section_hdr_32(nm, nm->bin_32.e_shstrndx);
	else
		sh_link = ft_get_section_hdr_32(nm, hdr->sh_link);
	if (!sh_link)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	str_tab = ft_get_section_content_32(nm, sh_link);
	if (!str_tab)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	if (sym->type == STT_SECTION)
		return (ft_symbol_get_name_section_32(nm, sym, str_tab));
	return (str_tab + sym->st_name);
}

static char	ft_symbol_get_type_link_algo_32(
	const t_Sym_32 *sym,
	char *name,
	u_int32_t sh_flags,
	u_int32_t sh_type
)
{
	if (sh_type == SHT_NOBITS)
		return (get_char_lower_upper('b', sym->bind == STB_GLOBAL));
	else if (sh_type == SHT_PROGBITS
		&& (sh_flags == (SHF_ALLOC | SHF_EXECINSTR)
			|| sh_flags == (SHF_ALLOC | SHF_EXECINSTR | SHF_WRITE)))
		return (get_char_lower_upper('t', sym->bind == STB_GLOBAL));
	else if (sym->type == STT_SECTION
		&& ft_strncmp(name, DEBUG_SECTION, ft_strlen(DEBUG_SECTION)) == 0)
		return (get_char_lower_upper('N', 0));
	else if ((sh_type == SHT_PROGBITS || sh_type == SHT_INIT_ARRAY
			|| sh_type == SHT_FINI_ARRAY || sh_type == SHT_DYNAMIC
			|| sh_type == SHT_PREINIT_ARRAY)
		&& ((sh_flags & (SHF_WRITE | SHF_ALLOC)) == (SHF_WRITE | SHF_ALLOC)))
		return (get_char_lower_upper('d', sym->bind == STB_GLOBAL));
	else if (sh_flags & SHF_ALLOC)
		return (get_char_lower_upper('r', sym->bind == STB_GLOBAL));
	else if (sym->type == STT_SECTION && (sh_type == SHT_SYMTAB
			|| sh_type == SHT_STRTAB))
		return (get_char_lower_upper('a', sym->bind == STB_GLOBAL));
	else if (sym->type == STT_SECTION)
		return (get_char_lower_upper('n', 0));
	return ('?');
}

static char	ft_symbol_get_type_link_32(
	t_nm *nm,
	const t_Sym_32 *sym,
	char *name
)
{
	const Elf32_Shdr	*hdr = ft_get_section_hdr_32(nm, sym->st_shndx);
	u_int32_t			sh_flags;
	u_int32_t			sh_type;

	if (!hdr)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (0);
	}
	sh_flags = swap_uint32(hdr->sh_flags, nm->global_infos.endian);
	sh_type = swap_uint32(hdr->sh_type, nm->global_infos.endian);
	return (ft_symbol_get_type_link_algo_32(sym, name, sh_flags, sh_type));
}

char	ft_symbol_get_type_32(t_nm *nm, const t_Sym_32 *sym, char *name)
{
	char	c;

	c = '?';
	if ((sym->type == STT_NOTYPE && sym->bind == STB_LOCAL
			&& sym->visibility == STV_DEFAULT && sym->st_shndx == SHN_UNDEF)
		|| sym->st_shndx == SHN_ABS)
		c = get_char_lower_upper('a', sym->bind == STB_GLOBAL);
	else if (sym->type == STT_LOOS)
		c = get_char_lower_upper('i', 0);
	else if (sym->type == STT_OBJECT && sym->bind == STB_WEAK)
		c = get_char_lower_upper('v', sym->st_shndx != SHN_UNDEF);
	else if (sym->bind == STB_WEAK)
		c = get_char_lower_upper('w', sym->st_shndx != SHN_UNDEF);
	else if (sym->st_shndx != SHN_ABS && sym->st_shndx != SHN_COMMON
		&& sym->st_shndx != SHN_UNDEF && sym->st_shndx != SHN_XINDEX)
	{
		c = ft_symbol_get_type_link_32(nm, sym, name);
		if (!c)
			return (c);
	}
	else if (sym->st_shndx == SHN_UNDEF)
		c = 'U';
	return (c);
}