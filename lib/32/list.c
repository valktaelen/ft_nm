/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:53 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 09:33:28 by aartiges         ###   ########lyon.fr   */
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

size_t	ft_list_size_32(t_symbol_32 *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		++i;
		lst = lst->next;
	}
	return (i);
}

static void	ft_switch_32(
	t_nm *nm,
	t_symbol_32 **current,
	t_symbol_32 **prev,
	t_symbol_32 **old
)
{
	(*prev)->next = (*current)->next;
	(*current)->next = *prev;
	if ((*prev) == nm->bin_32.syms)
		nm->bin_32.syms = (*current);
	else
		(*old)->next = (*current);
	(*prev) = *current;
	*current = (*prev)->next;
}

void	ft_list_sort_32(t_nm *nm)
{
	const size_t	len = ft_list_size_32(nm->bin_32.syms);
	t_symbol_32		*prev;
	t_symbol_32		*current;
	t_symbol_32		*old;
	size_t			i;

	i = 0;
	while (!(nm->flags & FLAG_NO_SORT) && i < len)
	{
		prev = nm->bin_32.syms;
		current = prev->next;
		while (current)
		{
			if (!(nm->flags & FLAG_REVERSE)
				&& ft_sort_string_symbol(prev->name, current->name) > 0)
				ft_switch_32(nm, &current, &prev, &old);
			else if ((nm->flags & FLAG_REVERSE)
				&& ft_sort_string_symbol(prev->name, current->name) < 0)
				ft_switch_32(nm, &current, &prev, &old);
			old = prev;
			prev = current;
			current = current->next;
		}
		++i;
	}
}
