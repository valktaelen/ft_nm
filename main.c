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
		printf("%s fd: %d size: %zu\n", file.prg_name, file.prg_fd, file.size);
		Elf64_Ehdr	*elf_hdr = get_elf_header(file.map, file.size);
		//print_elf_header_64(elf_hdr);
		//Elf64_Phdr	*prg_hdr = get_prg_header(file.map, file.size);
		//print_prg_header_64(prg_hdr);
		Elf64_Shdr	*section_header = get_first_section_header(file.map, file.size);
		int j = 0;
		// Elf64_Shdr	*shstrtab_hdr = (Elf64_Shdr*)(file.map + elf_hdr->e_shoff + elf_hdr->e_shentsize * elf_hdr->e_shstrndx);
		// char	*shstrtab = file.map + shstrtab_hdr->sh_offset;
		while (j < elf_hdr->e_shnum)
		{
			// if (section_header->sh_type == SHT_STRTAB)
			// 	print_section_header_64(section_header, shstrtab);
			if (section_header->sh_type == SHT_SYMTAB || section_header->sh_type == SHT_SYMTAB_SHNDX)
			{
				Elf64_Sym	*sym = file.map + section_header->sh_offset;
				while ((void *)sym < file.map + section_header->sh_offset + section_header->sh_size)
				{
					Elf64_Shdr	*str_section_hdr = (Elf64_Shdr*)(file.map + elf_hdr->e_shoff + elf_hdr->e_shentsize * section_header->sh_link);
					print_sym_64(sym, file.map + str_section_hdr->sh_offset);
					sym = (void *)sym + section_header->sh_entsize;
				}
			}
			section_header = get_next_section_header(file.map, file.size, section_header);
			++j;
		}
		munmap(file.map, file.size);
		close(file.prg_fd);
		++i;
	}
	return 0;
}

Elf64_Sym toto;