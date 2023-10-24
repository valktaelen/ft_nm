/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:58 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 10:30:13 by aartiges         ###   ########lyon.fr   */
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
