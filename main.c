/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:27 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/23 12:08:03 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_clean_nm(t_nm *nm)
{
	nm->fd = -1;
	nm->file_size = 0;
	nm->global_infos.arch = 0;
	nm->global_infos.endian = 0;
	nm->bin_64.e_shentsize = 0;
	nm->bin_64.e_shnum = 0;
	nm->bin_64.e_shoff = 0;
	nm->bin_64.e_shstrndx = 0;
	nm->bin_64.hdrs = NULL;
	if (nm->bin_64.syms)
		ft_clean_nm_64(nm->bin_64.syms);
	nm->bin_64.syms = NULL;
	nm->bin_32.e_shentsize = 0;
	nm->bin_32.e_shnum = 0;
	nm->bin_32.e_shoff = 0;
	nm->bin_32.e_shstrndx = 0;
	nm->bin_32.hdrs = NULL;
	if (nm->bin_32.syms)
		ft_clean_nm_32(nm->bin_32.syms);
	nm->bin_32.syms = NULL;
}

int	ft_nm(t_nm *nm, int index)
{
	int	ret;

	ft_clean_nm(nm);
	ret = 0;
	if (ft_check_file(nm) || ft_get_fd(nm))
		return (1);
	ret = ft_get_global_infos(nm);
	close(nm->fd);
	if (ret)
		return (1);
	if (nm->global_infos.arch == FT_64)
		ret = ft_nm_64(nm);
	else
		ret = ft_nm_32(nm);
	if (!ret)
	{
		if (nm->global_infos.arch == FT_64)
			ft_print_64(nm, index);
		else
			ft_print_32(nm, index);
	}
	munmap(nm->global_infos.map, nm->file_size);
	return (ret);
}

int	main(const int argc, char *argv[])
{
	t_nm		nm;
	int			i;
	int			ret;

	nm.prg_name = argv[0];
	nm.bin_64.syms = NULL;
	nm.bin_32.syms = NULL;
	if (argc == 1)
	{
		nm.file_path = DEFAULT_PRG;
		ret = ft_nm(&nm, 0);
	}
	else
	{
		i = 0;
		while (i < argc - 1)
		{
			nm.file_path = argv[i + 1];
			if (ft_nm(&nm, i + 1 - (argc == 2)))
				ret = 1;
			++i;
		}
	}
	ft_clean_nm(&nm);
	return (ret);
}
