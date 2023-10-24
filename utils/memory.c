/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:30 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 10:30:21 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_get_map(t_nm *nm, size_t len, off_t offset)
{
	void	*map;

	if (offset + len > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	map = mmap(NULL, len, PROT_READ, MAP_PRIVATE, nm->fd, offset);
	if (map == MAP_FAILED)
	{
		print_prg_error(nm, ERR_MAP_FAIL);
		return (NULL);
	}
	return (map);
}

t_Sym_64	*ft_get_symbol_64(t_nm *nm, Elf64_Sym *map_sym)
{
	const u_int8_t	endian = nm->global_infos.endian;
	t_Sym_64		*sym;

	sym = malloc(sizeof(t_Sym_64));
	if (!sym)
	{
		print_prg_error(nm, ERR_MALLOC);
		return (NULL);
	}
	sym->st_name = swap_uint32(map_sym->st_name, endian);
	sym->st_info = map_sym->st_info;
	sym->st_other = map_sym->st_other;
	sym->st_shndx = swap_uint16(map_sym->st_shndx, endian);
	sym->st_value = swap_uint64(map_sym->st_value, endian);
	sym->st_size = swap_uint64(map_sym->st_size, endian);
	sym->visibility = ELF64_ST_VISIBILITY(sym->st_other);
	sym->type = ELF64_ST_TYPE(sym->st_info);
	sym->bind = ELF64_ST_BIND(sym->st_info);
	return (sym);
}

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

t_S_hdr_32	*ft_get_section_32(t_nm *nm, Elf32_Shdr *map_hdr)
{
	const u_int8_t	endian = nm->global_infos.endian;
	t_S_hdr_32		*hdr;

	hdr = malloc(sizeof(t_S_hdr_32));
	if (!hdr)
		return (NULL);
	hdr->sh_name = swap_uint32(map_hdr->sh_name, endian);
	hdr->sh_type = swap_uint32(map_hdr->sh_type, endian);
	hdr->sh_flags = swap_uint32(map_hdr->sh_flags, endian);
	hdr->sh_offset = swap_uint32(map_hdr->sh_offset, endian);
	hdr->sh_size = swap_uint32(map_hdr->sh_size, endian);
	hdr->sh_link = swap_uint32(map_hdr->sh_link, endian);
	hdr->sh_info = swap_uint32(map_hdr->sh_info, endian);
	hdr->sh_entsize = swap_uint32(map_hdr->sh_entsize, endian);
	return (hdr);
}
