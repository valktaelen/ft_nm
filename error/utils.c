#include "error.h"

size_t	ft_strlen(const char *str)
{
	char	*s;

	if (!str)
		return (0);
	s = (char *)str;
	while (*s)
		++s;
	return (s - str);
}

int	ft_strncmp(const char *s1, const char *s2, const size_t n)
{
	size_t	i;

	if (s1 == s2 || n == 0)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = 0;
	while (i < n - 1 && *s1 == *s2 && *s1 && *s2)
	{
		++s1;
		++s2;
		++i;
	}
	return (*s1 - *s2);
}
