/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:27 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 10:40:13 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_check_file(t_nm *nm)
{
	struct stat	my_stat;

	errno = 0;
	if (stat(nm->file_path, &my_stat) != 0
		|| (!S_ISREG(my_stat.st_mode) && !S_ISLNK(my_stat.st_mode))
		|| my_stat.st_size < 0
		|| (size_t)my_stat.st_size < sizeof(Elf32_Ehdr))
	{
		if (!errno)
			print_prg_error(nm, ERR_FILE_RECONIZED);
		else if (errno == EACCES)
			print_prg_error(nm, ERR_FILE_ACCESS);
		else if (errno == ELOOP)
			print_prg_error(nm, ERR_FILE_MANY_SYM);
		else if (errno == ENAMETOOLONG)
			print_prg_error(nm, ERR_FILE_PATH_LONG);
		else if (errno == ENOENT)
			print_prg_error(nm, ERR_FILE_NO_EXIST);
		else
			print_prg_error(nm, ERR_FILE_NO_EXIST);
		return (1);
	}
	nm->file_size = my_stat.st_size;
	return (0);
}

int	ft_get_fd(t_nm *nm)
{
	nm->fd = open(nm->file_path, O_RDONLY);
	if (nm->fd == -1)
	{
		print_prg_error(nm, ERR_FILE_OPEN);
		return (1);
	}
	return (0);
}
