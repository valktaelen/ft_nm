/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:58 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 16:29:59 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	*ft_get_section_content_32(
	t_nm *nm,
	const Elf32_Shdr *hdr)
{
	const size_t	len = swap_uint32(hdr->sh_size, nm->global_infos.endian);
	const off_t		off = swap_uint32(hdr->sh_offset, nm->global_infos.endian);

	if (off + len > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	if (len == 0)
		return (NULL);
	return (nm->global_infos.map + off);
}

char	*ft_get_section_name_32(t_nm *nm, const Elf32_Shdr *hdr)
{
	const Elf32_Shdr	*str_hdr = ft_get_section_hdr_32(nm, nm->bin_32.e_shstrndx);
	const Elf32_Word	sh_name = swap_uint32(hdr->sh_name, nm->global_infos.endian);
	char				*str;

	if (!str_hdr)
		return (NULL);
	str = ft_get_section_content_32(nm, str_hdr);
	if (!str)
		return (NULL);
	return (str + sh_name);
}

