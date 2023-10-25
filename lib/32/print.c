/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:33 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 09:38:29 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

static void	ft_print_one_32(t_symbol_32 *sym)
{
	if (sym->type != 'U' && sym->type != 'w' && sym->type != 'v')
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

int	ft_need_print_32(t_nm *nm, t_symbol_32 *sym)
{
	int	ret;

	ret = 1;
	if (!(nm->flags & FLAG_ALL) && (sym->info_type == STT_FILE
			|| sym->info_type == STT_SECTION))
		ret = 0;
	else if ((nm->flags & FLAG_UNDEF) && sym->st_shndx != SHN_UNDEF)
		ret = 0;
	else if ((nm->flags & FLAG_EXTERN) && sym->bind == STB_LOCAL)
		ret = 0;
	return (ret);
}

void	ft_print_32(t_nm *nm, int index)
{
	t_symbol_32	*sym;

	sym = nm->bin_32.syms;
	if (index)
	{
		write(1, SEP_NL, 1);
		write(1, nm->file_path, ft_strlen(nm->file_path));
		write(1, SEP_1, 1);
		write(1, SEP_NL, 1);
	}
	if (!sym)
	{
		print_prg_error(nm, INFO_NO_SYM);
		return ;
	}
	while (sym)
	{
		if (ft_need_print_32(nm, sym))
			ft_print_one_32(sym);
		sym = sym->next;
	}
}
