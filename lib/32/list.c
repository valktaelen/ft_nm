/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:53 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 10:01:41 by aartiges         ###   ########lyon.fr   */
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

static u_int8_t	ft_switch_32(
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
	return (1);
}

void	ft_list_sort_32(t_nm *nm)
{
	t_symbol_32		*prev;
	t_symbol_32		*current;
	t_symbol_32		*old;
	t_symbol_32		*last;
	u_int8_t		i;

	i = 1;
	last = nm->bin_32.syms - 1;
	while (nm->bin_32.syms && !(nm->flags & FLAG_NO_SORT) && i)
	{
		prev = nm->bin_32.syms;
		current = prev->next;
		i = 0;
		while (current && current != last)
		{
			if ((!(nm->flags & FLAG_NO_SORT)
				&& ft_sort_string_symbol(prev->name, current->name) > 0)
				|| ((nm->flags & FLAG_NO_SORT)
				&& ft_sort_string_symbol(prev->name, current->name) < 0))
				i = ft_switch_32(nm, &current, &prev, &old);
			old = prev;
			prev = current;
			current = current->next;
		}
		last = prev;
	}
}
