#include "header.h"

#define DEFAULT_PRG "a.out"

int main(int argc, char *argv[])
{
	int	i;
	char	*prg;
	t_file	file;

	i = 0;
	while (i < argc)
	{
		if (argc > 1 && i == argc - 1)
			break;
		if (argc == 1)
			prg = DEFAULT_PRG;
		else
			prg = argv[i + 1];
		file = get_file_info(argv[0], prg);
		printf("%s %d %zu\n", file.prg_name, file.prg_fd, file.size);
		munmap(file.map, file.size);
		close(file.prg_fd);
		++i;
	}
	return 0;
}

