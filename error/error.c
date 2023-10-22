#include "error.h"

void	print_prg_error_file(t_file *file, char *error, u_int8_t is_errno)
{
	char	*err_str;

	write(STDERR_FILENO, file->prg_name, ft_strlen(file->prg_name));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, file->file_path, ft_strlen(file->file_path));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, error, ft_strlen(error));
	if (is_errno)
	{
		write(STDERR_FILENO, SEP_SPACE, ft_strlen(SEP_SPACE));
		err_str = strerror(errno);
		write(STDERR_FILENO, err_str, ft_strlen(err_str));
	}
	write(STDERR_FILENO, SEP_NL, ft_strlen(SEP_NL));
}

void	print_prg_error(char *file_path, char *error, u_int8_t is_errno)
{
	char	*err_str;

	write(STDERR_FILENO, file_path, ft_strlen(file_path));
	write(STDERR_FILENO, SEP_1, ft_strlen(SEP_1));
	write(STDERR_FILENO, error, ft_strlen(error));
	if (is_errno)
	{
		write(STDERR_FILENO, SEP_SPACE, ft_strlen(SEP_SPACE));
		err_str = strerror(errno);
		write(STDERR_FILENO, err_str, ft_strlen(err_str));
	}
	write(STDERR_FILENO, SEP_NL, ft_strlen(SEP_NL));
}
