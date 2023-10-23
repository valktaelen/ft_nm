/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:13 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/23 07:27:18 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

static void	ft_print_one_64(t_symbol_64 *sym)
{
	if (sym->type != 'U' && sym->type != 'w')
		print_number_n_digit(sym->st_value, 8);
	else if (
		(sym->info_type == STT_NOTYPE
			&& sym->bind == STB_LOCAL
			&& sym->visibility == STV_DEFAULT
			&& sym->st_shndx == SHN_UNDEF)
		|| sym->st_shndx == SHN_ABS || sym->info_type == STT_SECTION)
		print_number_n_digit(0, 8);
	else
		write(1, "        ", 8);
	write(1, SEP_SPACE, 1);
	write(1, &sym->type, 1);
	write(1, SEP_SPACE, 1);
	write(1, sym->name, ft_strlen(sym->name));
	write(1, SEP_NL, 1);
}

void	ft_print_64(t_nm *nm, int index)
{
	t_symbol_64	*sym;

	sym = nm->bin_64.syms;
	if (!sym)
	{
		print_prg_error(nm, INFO_NO_SYM);
		return ;
	}
	if (index)
	{
		write(1, SEP_NL, 1);
		write(1, nm->file_path, ft_strlen(nm->file_path));
		write(1, SEP_1, 1);
		write(1, SEP_NL, 1);
	}
	while (sym)
	{
		ft_print_one_64(sym);
		sym = sym->next;
	}
}
