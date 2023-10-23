/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:16 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/23 06:57:25 by aartiges         ###   ########lyon.fr   */
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

t_S_hdr_64	*ft_get_section_64(t_nm *nm, Elf64_Shdr *map_hdr)
{
	const u_int8_t	endian = nm->global_infos.endian;
	t_S_hdr_64		*hdr;

	hdr = malloc(sizeof(t_S_hdr_64));
	if (!hdr)
		return (NULL);
	hdr->sh_name = swap_uint32(map_hdr->sh_name, endian);
	hdr->sh_type = swap_uint32(map_hdr->sh_type, endian);
	hdr->sh_flags = swap_uint64(map_hdr->sh_flags, endian);
	hdr->sh_offset = swap_uint64(map_hdr->sh_offset, endian);
	hdr->sh_size = swap_uint64(map_hdr->sh_size, endian);
	hdr->sh_link = swap_uint32(map_hdr->sh_link, endian);
	hdr->sh_info = swap_uint32(map_hdr->sh_info, endian);
	hdr->sh_entsize = swap_uint64(map_hdr->sh_entsize, endian);
	return (hdr);
}
