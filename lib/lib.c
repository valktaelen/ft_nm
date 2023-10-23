#include "lib.h"

int	ft_get_global_infos(t_nm *nm)
{
	Elf32_Ehdr	*elf_hdr;

	elf_hdr = ft_get_map(nm, nm->file_size, 0);
	if (!elf_hdr)
		return (1);
	nm->global_infos.endian = elf_hdr->e_ident[EI_DATA];
	nm->global_infos.arch = elf_hdr->e_ident[EI_CLASS];
	if (!(nm->global_infos.endian == FT_LITTLE_ENDIAN
		|| nm->global_infos.endian == FT_BIG_ENDIAN)
		|| !(nm->global_infos.arch == FT_32
		|| nm->global_infos.arch == FT_64)
		|| !(elf_hdr->e_ident[EI_MAG0] == ELFMAG0
			&& elf_hdr->e_ident[EI_MAG1] == ELFMAG1
			&& elf_hdr->e_ident[EI_MAG2] == ELFMAG2
			&& elf_hdr->e_ident[EI_MAG3] == ELFMAG3))
	{
		print_prg_error(nm, ERR_FILE_RECONIZED);
		munmap((void *)elf_hdr, nm->file_size);
		return (1);
	}
	nm->global_infos.map = (void *)elf_hdr;
	return (0);
}
