/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:53 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/23 08:27:56 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	ft_clean_nm_32(t_symbol_32 *syms)
{
	t_symbol_32	*sym;

	while (syms)
	{
		sym = syms;
		syms = syms->next;
		free(sym);
	}
}

void	ft_list_sym_add_32(t_nm *nm, t_symbol_32 *sym)
{
	t_symbol_32	*symbol;

	sym->next = NULL;
	if (nm->bin_32.syms)
	{
		symbol = nm->bin_32.syms;
		while (symbol->next)
			symbol = symbol->next;
		symbol->next = sym;
	}
	else
		nm->bin_32.syms = sym;
}
