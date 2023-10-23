#include "utils.h"

size_t	ft_strlen(char * str)
{
	char	*s;

	if (!str)
		return (0);
	s = str;
	while (*s)
		++s;
	return (s - str);
}

int	ft_strncmp(char *s1, char *s2, const size_t n)
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

void	print_prg_error(t_nm *nm, char *error)
{
	write(STDERR_FILENO, nm->prg_name, ft_strlen(nm->prg_name));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, nm->file_path, ft_strlen(nm->file_path));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, SEP_NL, ft_strlen(SEP_NL));
}

char	*ft_strdup(char *str)
{
	const size_t	len = ft_strlen(str);
	char			*ret;
	size_t			i;

	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		ret[i] = str[i];
		++i;
	}
	return (ret);
}

void	print_number_n_digit(Elf64_Addr n, size_t digit)
{
	static char	*base = "0123456789abcdef";

	while (digit)
		write(1, base + ((n >> (--digit * 4)) % 16), 1);
}

char	get_char_lower_upper(char lower_letter, u_int8_t to_upper)
{
	if (to_upper)
		lower_letter += 'A' - 'a';
	return lower_letter;
}
