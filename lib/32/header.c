/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:30 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 15:14:47 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

Elf32_Shdr	*ft_get_section_hdr_32(t_nm *nm, Elf32_Half i_table)
{
	const Elf32_Off	len = nm->bin_32.e_shnum * nm->bin_32.e_shentsize;
	const Elf32_Off	offset = nm->bin_32.e_shentsize * i_table;

	if (offset >= len)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	return (((void *)nm->bin_32.hdrs) + offset);
}

Elf32_Phdr	*ft_get_prg_hdr_32(t_nm *nm, Elf32_Half i_table)
{
	const Elf32_Half	len = nm->bin_32.e_phnum * nm->bin_32.e_phentsize;
	const Elf32_Half	offset = nm->bin_32.e_phentsize * i_table;

	if (offset >= len)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	return (((void *)nm->bin_32.prg_hdrs) + offset);
}

int	ft_get_section_hdrs_32(t_nm *nm)
{
	if (nm->bin_32.e_shoff == 0
		|| nm->bin_32.e_shentsize < sizeof(Elf32_Shdr)
		|| nm->bin_32.e_shnum == 0
		|| nm->bin_32.e_shoff + nm->bin_32.e_shentsize * nm->bin_32.e_shnum
		> nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (1);
	}
	nm->bin_32.hdrs = nm->global_infos.map + nm->bin_32.e_shoff;
	return (nm->bin_32.hdrs == NULL);
}

int	ft_get_prg_hdrs_32(t_nm *nm)
{
	if (nm->bin_32.e_phoff == 0
		|| nm->bin_32.e_phentsize < sizeof(Elf32_Phdr)
		|| nm->bin_32.e_phnum == 0
		|| nm->bin_32.e_phoff
		+ nm->bin_32.e_phentsize * nm->bin_32.e_phnum > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (1);
	}
	nm->bin_32.prg_hdrs = nm->global_infos.map + nm->bin_32.e_phoff;
	return (nm->bin_32.prg_hdrs == NULL);
}

int	ft_get_elf_hdr_infos_32(t_nm *nm)
{
	const size_t	len = sizeof(Elf32_Ehdr);
	const u_int8_t	endian = nm->global_infos.endian;
	Elf32_Ehdr		*elf_hdr;
	int				ret;

	if (len > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (1);
	}
	elf_hdr = nm->global_infos.map;
	if (!elf_hdr)
		return (1);
	nm->bin_32.e_shoff = swap_uint32(elf_hdr->e_shoff, endian);
	nm->bin_32.e_shentsize = swap_uint16(elf_hdr->e_shentsize, endian);
	nm->bin_32.e_shnum = swap_uint16(elf_hdr->e_shnum, endian);
	nm->bin_32.e_shstrndx = swap_uint16(elf_hdr->e_shstrndx, endian);
	nm->bin_32.e_phoff = swap_uint32(elf_hdr->e_phoff, endian);
	nm->bin_32.e_ehsize = swap_uint16(elf_hdr->e_ehsize, endian);
	nm->bin_32.e_phentsize = swap_uint16(elf_hdr->e_phentsize, endian);
	nm->bin_32.e_phnum = swap_uint16(elf_hdr->e_phnum, endian);
	ret = 0;
	if (ft_get_section_hdrs_32(nm))
		ret = 1;
	if (ft_get_prg_hdrs_32(nm))
		ret = 1;
	return (ret);
}
