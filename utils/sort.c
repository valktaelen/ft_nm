/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 07:59:59 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/25 03:14:40 by aartiges         ###   ########lyon.fr   */
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

static int	ft_strcmp_symbol(char *s1, char *s2)
{
	if (*s1 == '%')
		++s1;
	if (*s2 == '%')
		++s2;
	if (*s1 == '$' && (*s2 != '$' && *s2 != 0))
		return (-1);
	if ((*s1 != '$' && *s1 != 0) && *s2 == '$')
		return (1);
	while (*s1 && *s2)
	{
		while (*s1 && !((*s1 >= 'a' && *s1 <= 'z') || (*s1 >= 'A' && *s1 <= 'Z')
				|| (*s1 >= '0' && *s1 <= '9')))
			++s1;
		while (*s2 && !((*s2 >= 'a' && *s2 <= 'z') || (*s2 >= 'A' && *s2 <= 'Z')
				|| (*s2 >= '0' && *s2 <= '9')))
			++s2;
		if (!*s1 || !*s2 || ft_cmp_letter(*s1, *s2))
			break ;
		++s1;
		++s2;
	}
	return (ft_cmp_letter(*s1, *s2));
}

int	ft_strcmp_symbol_prefix(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

int	ft_cmp_case(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		while (*s1 && !((*s1 >= 'a' && *s1 <= 'z') || (*s1 >= 'A' && *s1 <= 'Z')
				|| (*s1 >= '0' && *s1 <= '9')))
			++s1;
		while (*s2 && !((*s2 >= 'a' && *s2 <= 'z') || (*s2 >= 'A' && *s2 <= 'Z')
				|| (*s2 >= '0' && *s2 <= '9')))
			++s2;
		if (!*s1 || !*s2 || *s1 != *s2)
			break ;
		++s1;
		++s2;
	}
	return (*s2 - *s1);
}

int	ft_sort_string_symbol(char *s1, char *s2)
{
	int		ret;

	ret = ft_strcmp_symbol(s1, s2);
	if (ret == 0)
	{
		ret = ft_cmp_case(s1, s2);
		if (ret == 0)
			ret = (ft_strcmp_symbol_prefix(s1, s2));
	}
	return (ret);
}
