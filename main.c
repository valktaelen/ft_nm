#include "header.h"

#define DEFAULT_PRG "a.out"
#define CORRUPT_FILE "Corrupt file"

u_int8_t	ft_nm_64(t_binary_64 *bin)
{
	Elf64_Shdr	*section_hdr;

	// printf("%s size: %zu\n", bin->file.prg_name, bin->file.size);
	size_t i = 0;
	while (i < bin->elf_hdr->e_shnum)
	{
		section_hdr = get_n_section_header_64(bin, i);
		if (section_hdr->sh_type == SHT_SYMTAB || section_hdr->sh_type == SHT_SYMTAB_SHNDX)
		{
			Elf64_Sym	*sym = bin->file.map + section_hdr->sh_offset;
			while ((void *)sym < bin->file.map + section_hdr->sh_offset + section_hdr->sh_size)
			{
				Elf64_Shdr	*str_section_hdr = get_n_section_header_64(bin, section_hdr->sh_link);
				print_sym_64(sym, bin->file.map + str_section_hdr->sh_offset, bin);
				sym = (void *)sym + section_hdr->sh_entsize;
			}
		}
		++i;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	int			i;
	char		*prg;
	t_binary_64	bin;

	i = 0;
	while (i < argc - 1 + (argc == 1))
	{
		if (argc == 1)
			prg = DEFAULT_PRG;
		else
			prg = argv[i + 1];
		bin.file = get_file_info(argv[0], prg);
		if (!bin.file.map || !bin.file.size)
		{
			++i;
			continue ;
		}
		if (get_binary_64(&bin))
		{
			print_prg_error_file(&bin.file, CORRUPT_FILE, 0);
			munmap(bin.file.map, bin.file.size);
			++i;
			continue ;
		}
		ft_nm_64(&bin);
		munmap(bin.file.map, bin.file.size);
		++i;
	}
	return 0;
}

Elf64_Sym toto;