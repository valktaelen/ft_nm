#include "utils.h"

void	*ft_get_map(t_nm *nm, size_t len, off_t offset)
{
	void	*map;

	if (offset + len > nm->file_size)
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		return (NULL);
	}
	map = mmap(NULL, len, PROT_READ, MAP_PRIVATE, nm->fd, offset);
	if (map == MAP_FAILED)
	{
		print_prg_error(nm, ERR_MAP_FAIL);
		perror(NULL);
		return (NULL);
	}
	return (map);
}
