/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:27 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/25 13:34:36 by aartiges         ###   ########lyon.fr   */
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

int	get_flag(char *arg)
{
	char	c;

	if (ft_strlen(arg) != 2)
		return (FLAG_NO);
	c = arg[1];
	if (c == 'a')
		return (FLAG_ALL);
	if (c == 'r')
		return (FLAG_REVERSE);
	if (c == 'g')
		return (FLAG_EXTERN);
	if (c == 'p')
		return (FLAG_NO_SORT);
	if (c == 'u')
		return (FLAG_UNDEF);
	return (FLAG_NO);
}

int	ft_init_prg(const int argc, char **argv, t_nm *nm)
{
	u_int8_t	tmp;
	int			i;

	nm->bin_64.syms = NULL;
	nm->bin_32.syms = NULL;
	nm->flags = FLAG_NO;
	nm->nb_file = 0;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			tmp = get_flag(argv[i]);
			if (tmp == FLAG_NO)
			{
				print_parsing_error(nm, ERR_INV_OPTION, argv[i] + 1);
				return (1);
			}
			nm->flags |= tmp;
		}
		else
			nm->nb_file += 1;
		++i;
	}
	return (0);
}

int	main(const int argc, char *argv[])
{
	t_nm		nm;
	int			i;
	int			tmp;
	int			ret;

	nm.prg_name = argv[0];
	if (ft_init_prg(argc, argv, &nm))
		return (1);
	i = 0;
	ret = 0;
	while (i < argc)
	{
		nm.file_path = DEFAULT_PRG;
		if (nm.nb_file)
			nm.file_path = argv[i];
		if (nm.file_path[0] != '-' && ((i == 0 && !nm.nb_file) || i > 0))
		{
			tmp = ft_nm(&nm, nm.nb_file > 1);
			if (tmp)
				++ret;
		}
		++i;
	}
	ft_clean_nm(&nm);
	return (ret);
}
