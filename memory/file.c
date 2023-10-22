#include "memory.h"

size_t	get_file_size(const char *file_path)
{
	struct stat	my_stat;

	if (stat(file_path, &my_stat) != 0)
		return 0;
	if (!S_ISREG(my_stat.st_mode) && !S_ISLNK(my_stat.st_mode))
		return (0);
	return my_stat.st_size;
}

t_file	get_file_info(char *prg_name, char *file_path)
{
	const int		fd = open(file_path, O_RDONLY);
	const size_t	size = get_file_size(file_path);
	void			*map;

	if (fd == -1)
		print_prg_error(prg_name, file_path, 1);
	else if (size)
	{
		map = mmap(NULL, size, PROT_EXEC, MAP_PRIVATE, fd, 0);
		if (map == (void *) -1) {
			print_prg_error(prg_name, file_path, 1);
			map = NULL;
		}
	}
	close(fd);
	return (t_file){
		.prg_name = prg_name,
		.file_path = file_path,
		.map = map,
		.size = size
	};
}
