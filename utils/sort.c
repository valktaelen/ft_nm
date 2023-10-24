/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 07:59:59 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/24 06:35:14 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_cmp_letter(char c1, char c2)
{
	if (c1 >= 'a' && c1 <= 'z' && c2 >= 'A' && c2 <= 'Z')
		return ((c1 - 'a') - (c2 - 'A'));
	if (c1 >= 'A' && c1 <= 'Z' && c2 >= 'a' && c2 <= 'z')
		return ((c1 - 'A') - (c2 - 'a'));
	return (c1 - c2);
}

static int	ft_is_letter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

static int	ft_strcmp_symbol(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (!ft_is_letter(*s1))
		{
			++s1;
			continue ;
		}
		if (!ft_is_letter(*s2))
		{
			++s2;
			continue ;
		}
		if (ft_cmp_letter(*s1, *s2))
			break ;
		++s1;
		++s2;
	}
	return (ft_cmp_letter(*s1, *s2));
}

static int	ft_strcmp_symbol_prefix(char *s1, char *s2)
{
	while (*s1 && *s2 && ft_cmp_letter(*s1, *s2) == 0)
	{
		++s1;
		++s2;
	}
	return (ft_cmp_letter(*s1, *s2));
}

int	ft_sort_string_symbol(char *s1, char *s2)
{
	int		ret;

	ret = ft_strcmp_symbol(s1, s2);
	if (ret == 0)
		return (ft_strcmp_symbol_prefix(s1, s2));
	return (ret);
}
