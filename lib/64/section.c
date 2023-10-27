/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:16 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 16:26:04 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	*ft_get_section_content_64(
	t_nm *nm,
	const Elf64_Shdr *hdr)
{
	const size_t	len = swap_uint64(hdr->sh_size, nm->global_infos.endian);
	const off_t		off = swap_uint64(hdr->sh_offset, nm->global_infos.endian);

	if (off + len > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	if (len == 0)
		return (NULL);
	return (nm->global_infos.map + off);
}

char	*ft_get_section_name_64(t_nm *nm, const Elf64_Shdr *hdr)
{
	const Elf64_Shdr	*str_hdr = ft_get_section_hdr_64(nm, nm->bin_64.e_shstrndx);
	const Elf64_Word	sh_name = swap_uint32(hdr->sh_name, nm->global_infos.endian);
	char				*str;

	if (!str_hdr)
		return (NULL);
	str = ft_get_section_content_64(nm, str_hdr);
	if (!str)
		return (NULL);
	return (str + sh_name);
}
