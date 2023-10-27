/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:52:10 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 10:01:50 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	ft_clean_nm_64(t_symbol_64 *syms)
{
	t_symbol_64	*sym;

	while (syms)
	{
		sym = syms;
		syms = syms->next;
		free(sym);
	}
}

void	ft_list_sym_add_64(t_nm *nm, t_symbol_64 *sym)
{
	t_symbol_64	*symbol;

	sym->next = NULL;
	if (nm->bin_64.syms)
	{
		symbol = nm->bin_64.syms;
		while (symbol->next)
			symbol = symbol->next;
		symbol->next = sym;
	}
	else
		nm->bin_64.syms = sym;
}

size_t	ft_list_size_64(t_symbol_64 *lst)
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

static u_int8_t	ft_switch_64(
	t_nm *nm,
	t_symbol_64 **current,
	t_symbol_64 **prev,
	t_symbol_64 **old
)
{
	(*prev)->next = (*current)->next;
	(*current)->next = *prev;
	if ((*prev) == nm->bin_64.syms)
		nm->bin_64.syms = (*current);
	else
		(*old)->next = (*current);
	(*prev) = *current;
	*current = (*prev)->next;
	return (1);
}

void	ft_list_sort_64(t_nm *nm)
{
	t_symbol_64		*prev;
	t_symbol_64		*current;
	t_symbol_64		*old;
	t_symbol_64		*last;
	u_int8_t		i;

	i = 1;
	last = nm->bin_64.syms - 1;
	while (nm->bin_64.syms && !(nm->flags & FLAG_NO_SORT) && i)
	{
		prev = nm->bin_64.syms;
		current = prev->next;
		i = 0;
		while (current && current != last)
		{
			if ((!(nm->flags & FLAG_REVERSE)
				&& ft_sort_string_symbol(prev->name, current->name) > 0)
				|| ((nm->flags & FLAG_REVERSE)
				&& ft_sort_string_symbol(prev->name, current->name) < 0))
				i = ft_switch_64(nm, &current, &prev, &old);
			old = prev;
			prev = current;
			current = current->next;
		}
		last = prev;
	}
}
