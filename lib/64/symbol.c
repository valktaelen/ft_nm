/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:01 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 15:18:54 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

static char	*ft_symbol_get_name_section_64(t_nm *nm,
	const t_Sym_64 *sym,
	char *str_tab)
{
	Elf64_Shdr	*sh_link_sym;

	sh_link_sym = ft_get_section_hdr_64(nm, sym->st_shndx);
	if (!sh_link_sym)
		return (NULL);
	return (
		str_tab + swap_uint32(sh_link_sym->sh_name, nm->global_infos.endian)
	);
}

char	*ft_symbol_get_name_64(t_nm *nm, const t_S_hdr_64 *hdr,
	const t_Sym_64 *sym)
{
	Elf64_Shdr	*sh_link;
	char		*str_tab;

	if (sym->type == STT_SECTION)
		sh_link = ft_get_section_hdr_64(nm, nm->bin_64.e_shstrndx);
	else
		sh_link = ft_get_section_hdr_64(nm, hdr->sh_link);
	if (!sh_link)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	str_tab = ft_get_section_content_64(nm, sh_link);
	if (!str_tab)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	if (sym->type == STT_SECTION)
		return (ft_symbol_get_name_section_64(nm, sym, str_tab));
	return (str_tab + sym->st_name);
}

static char	ft_symbol_get_type_link_algo_64(
	const t_Sym_64 *sym,
	char *name,
	u_int64_t sh_flags,
	u_int64_t sh_type
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
	else if (sym->type == STT_SECTION || sh_flags == 0)
		return (get_char_lower_upper('n', 0));
	return ('?');
}

char	ft_get_type_by_segment_64(t_nm *nm, const t_Sym_64 *sym)
{
	const Elf64_Shdr	*hdr = ft_get_section_hdr_64(nm, sym->st_shndx);
	Elf64_Phdr	*p_hdr;
	Elf64_Half	i;
	Elf64_Off	start;
	Elf64_Off	end;
	Elf64_Off	start_section;
	Elf64_Word	p_type;
	Elf64_Word	p_flags;

	i = 0;
	while (i < nm->bin_64.e_phnum)
	{
		p_hdr = ft_get_prg_hdr_64(nm, i);
		start = swap_uint64(p_hdr->p_offset, nm->global_infos.endian);
		end = start + swap_uint64(p_hdr->p_filesz, nm->global_infos.endian);
		start_section = swap_uint64(hdr->sh_offset, nm->global_infos.endian);
		if (start <= start_section && start_section < end)
		{
			p_type = swap_uint32(p_hdr->p_type, nm->global_infos.endian);
			p_flags = swap_uint32(p_hdr->p_flags, nm->global_infos.endian);
			if (p_type == PT_LOAD && p_flags == (PF_W | PF_R))
				return (get_char_lower_upper('d', sym->bind == STB_GLOBAL));
			if (p_type == PT_LOAD && p_flags == (PF_R))
				return (get_char_lower_upper('r', sym->bind == STB_GLOBAL));
			if (p_type == PT_LOAD && p_flags == (PF_R | PF_X))
				return (get_char_lower_upper('t', sym->bind == STB_GLOBAL));
			if (p_type == PT_GNU_STACK)
				return (get_char_lower_upper('p', 0));
		}
		++i;
	}
	return 0;
}

static char	ft_symbol_get_type_link_64(
	t_nm *nm,
	const t_Sym_64 *sym,
	char *name
)
{
	const Elf64_Shdr	*hdr = ft_get_section_hdr_64(nm, sym->st_shndx);
	u_int64_t			sh_flags;
	u_int64_t			sh_type;
	char				c;

	if (!hdr)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (0);
	}
	c = ft_get_type_by_segment_64(nm, sym);
	if (c)
		return (c);
	sh_flags = swap_uint64(hdr->sh_flags, nm->global_infos.endian);
	sh_type = swap_uint64(hdr->sh_type, nm->global_infos.endian);
	return (ft_symbol_get_type_link_algo_64(sym, name, sh_flags, sh_type));
}

char	ft_symbol_get_type_64(t_nm *nm, const t_Sym_64 *sym, char *name)
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
		c = ft_symbol_get_type_link_64(nm, sym, name);
		if (!c)
			return (c);
		//printf("%c\n", c);
	}
	else if (sym->st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym->st_shndx == SHN_COMMON)
		c = 'C';
	return (c);
}
