/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:16 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 10:28:27 by aartiges         ###   ########lyon.fr   */
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
