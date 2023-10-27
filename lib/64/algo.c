/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:04 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 16:07:32 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

static t_symbol_64	*ft_nm_symbol_create_64(
	t_nm *nm,
	const t_Sym_64 *sym,
	char *name
)
{
	t_symbol_64	*node_sym;

	node_sym = malloc(sizeof(t_symbol_64));
	if (!node_sym)
	{
		print_prg_error(nm, ERR_MALLOC);
		return (NULL);
	}
	node_sym->st_value = sym->st_value;
	node_sym->name = name;
	node_sym->type = ft_symbol_get_type_64(nm, sym, name);
	if (!node_sym->type)
	{
		free(node_sym);
		return (NULL);
	}
	node_sym->st_shndx = sym->st_shndx;
	node_sym->visibility = sym->visibility;
	node_sym->info_type = sym->type;
	node_sym->bind = sym->bind;
	return (node_sym);
}

int	ft_nm_symbol_64(t_nm *nm, const t_S_hdr_64 *hdr, Elf64_Sym *map_sym)
{
	const t_Sym_64	*sym = ft_get_symbol_64(nm, map_sym);
	t_symbol_64		*node_sym;
	char			*name;

	if (!sym)
		return (1);
	name = ft_symbol_get_name_64(nm, hdr, sym);
	if (!name)
	{
		free((void *)sym);
		return (0);
	}
	node_sym = ft_nm_symbol_create_64(nm, sym, name);
	free((void *)sym);
	if (!node_sym)
		return (1);
	ft_list_sym_add_64(nm, node_sym);
	return (0);
}

int	ft_nm_section_64(t_nm *nm, const Elf64_Shdr *hdr)
{
	const t_S_hdr_64	*s_hdr = ft_get_section_64(nm, (Elf64_Shdr *)hdr);
	Elf64_Sym			*symbols;
	Elf64_Xword			offset;

	if (!s_hdr)
		return (1);
	if (s_hdr->sh_type == SHT_SYMTAB || s_hdr->sh_type == SHT_SYMTAB_SHNDX)
	{
		symbols = ft_get_section_content_64(nm, (Elf64_Shdr *)hdr);
		if (!symbols)
		{
			print_prg_error(nm, ERR_FILE_RECONIZED);
			free((void *)s_hdr);
			return (1);
		}
		offset = 0;
		while (offset < s_hdr->sh_size)
		{
			if (ft_nm_symbol_64(nm, s_hdr, (void *)symbols + offset))
				break ;
			offset += s_hdr->sh_entsize;
		}
	}
	free((void *)s_hdr);
	return (0);
}

int	ft_nm_64(t_nm *nm)
{
	Elf64_Half	i_section;
	Elf64_Shdr	*section;
	t_symbol_64	*node_sym;

	if (ft_get_elf_hdr_infos_64(nm))
		return (1);
	i_section = 0;
	while (i_section < nm->bin_64.e_shnum)
	{
		section = ft_get_section_hdr_64(nm, i_section);
		if (!section || ft_nm_section_64(nm, section))
		{
			nm->bin_64.hdrs = NULL;
			return (1);
		}
		++i_section;
	}
	nm->bin_64.hdrs = NULL;
	node_sym = nm->bin_64.syms;
	if (node_sym)
	{
		nm->bin_64.syms = node_sym->next;
		free(node_sym);
	}
	ft_list_sort_64(nm);
	return (0);
}
