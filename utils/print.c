/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:32:40 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 10:32:41 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_prg_error(t_nm *nm, char *error)
{
	write(STDERR_FILENO, nm->prg_name, ft_strlen(nm->prg_name));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, nm->file_path, ft_strlen(nm->file_path));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, SEP_NL, ft_strlen(SEP_NL));
}

void	print_parsing_error(t_nm *nm, char *error, char *val)
{
	write(STDERR_FILENO, nm->prg_name, ft_strlen(nm->prg_name));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, val, ft_strlen(val));
	write(STDERR_FILENO, SEP_NL, ft_strlen(SEP_NL));
}
