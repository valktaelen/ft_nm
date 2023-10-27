/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:07 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 13:45:07 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

Elf64_Shdr	*ft_get_section_hdr_64(t_nm *nm, Elf64_Half i_table)
{
	const Elf64_Half	len = nm->bin_64.e_shnum * nm->bin_64.e_shentsize;
	const Elf64_Half	offset = nm->bin_64.e_shentsize * i_table;

	if (offset >= len)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	return (((void *)nm->bin_64.hdrs) + offset);
}

Elf64_Phdr	*ft_get_prg_hdr_64(t_nm *nm, Elf64_Half i_table)
{
	const Elf64_Half	len = nm->bin_64.e_phnum * nm->bin_64.e_phentsize;
	const Elf64_Half	offset = nm->bin_64.e_phentsize * i_table;

	if (offset >= len)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	return (((void *)nm->bin_64.prg_hdrs) + offset);
}

int	ft_get_section_hdrs_64(t_nm *nm)
{
	if (nm->bin_64.e_shoff == 0
		|| nm->bin_64.e_shentsize < sizeof(Elf64_Shdr)
		|| nm->bin_64.e_shnum == 0
		|| nm->bin_64.e_shoff
		+ nm->bin_64.e_shentsize * nm->bin_64.e_shnum > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (1);
	}
	nm->bin_64.hdrs = nm->global_infos.map + nm->bin_64.e_shoff;
	return (nm->bin_64.hdrs == NULL);
}

int	ft_get_prg_hdrs_64(t_nm *nm)
{
	if (nm->bin_64.e_phoff == 0
		|| nm->bin_64.e_phentsize < sizeof(Elf64_Phdr)
		|| nm->bin_64.e_phnum == 0
		|| nm->bin_64.e_phoff
		+ nm->bin_64.e_phentsize * nm->bin_64.e_phnum > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (1);
	}
	nm->bin_64.prg_hdrs = nm->global_infos.map + nm->bin_64.e_phoff;
	return (nm->bin_64.prg_hdrs == NULL);
}

int	ft_get_elf_hdr_infos_64(t_nm *nm)
{
	const size_t	len = sizeof(Elf64_Ehdr);
	const u_int8_t	endian = nm->global_infos.endian;
	Elf64_Ehdr		*elf_hdr;
	int				ret;

	if (len > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (1);
	}
	elf_hdr = nm->global_infos.map;
	if (!elf_hdr)
		return (1);
	nm->bin_64.e_shoff = swap_uint64(elf_hdr->e_shoff, endian);
	nm->bin_64.e_shentsize = swap_uint16(elf_hdr->e_shentsize, endian);
	nm->bin_64.e_shnum = swap_uint16(elf_hdr->e_shnum, endian);
	nm->bin_64.e_shstrndx = swap_uint16(elf_hdr->e_shstrndx, endian);
	nm->bin_64.e_phoff = swap_uint64(elf_hdr->e_phoff, endian);
	nm->bin_64.e_ehsize = swap_uint16(elf_hdr->e_ehsize, endian);
	nm->bin_64.e_phentsize = swap_uint16(elf_hdr->e_phentsize, endian);
	nm->bin_64.e_phnum = swap_uint16(elf_hdr->e_phnum, endian);
	ret = 0;
	if (ft_get_section_hdrs_64(nm))
		ret = 1;
	if (ft_get_prg_hdrs_64(nm))
		ret = 1;
	return (ret);
}
