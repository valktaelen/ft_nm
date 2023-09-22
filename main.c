#include "header.h"

u_int8_t	get_arch(const void *const map)
{
	const unsigned char	*e_ident = map;
	u_int8_t			magic;

	magic = e_ident[EI_MAG0] == 0x7f && e_ident[EI_MAG1] == 'E'
			&& e_ident[EI_MAG2] == 'L' && e_ident[EI_MAG3] == 'F';
	if (magic && e_ident[EI_CLASS] == ELFCLASS32)
		return 32;
	if (magic && e_ident[EI_CLASS] == ELFCLASS64)
		return 64;
	return 0;
}

#define ERR_NO_PRG "« a.out »: pas de tel fichier"

void print_prg(const char *prg, const char *prefix, const char *error) {
	if (prefix) {
		write(2, prefix, strlen(prefix));
		write(2, " - ", 3);
	}
	if (error) {
		write(2, prg, strlen(prg));
		write(2, ": ", 2);
		write(2, error, strlen(error));
		write(2, "\n", 1);
	} else {
		perror(prg);
	}
}

void	print_header(void *map) {
	Elf32_Ehdr	*header32 = map;
	printf("e_ident ");
	for (int i = 0; i < EI_NIDENT;i++) {
		printf("%c", header32->e_ident[i]);
	}
	printf("\n");
	printf("e_type %d\n", header32->e_type);
	printf("e_machine %d\n", header32->e_machine);
	printf("e_version %d\n", header32->e_version);
	printf("e_entry %d\n", header32->e_entry);
	printf("e_phoff %d\n", header32->e_phoff);
	printf("e_shoff %d\n", header32->e_shoff);
	printf("e_flags %d\n", header32->e_flags);
	printf("e_ehsize %d\n", header32->e_ehsize);
	printf("e_phentsize %d\n", header32->e_phentsize);
	printf("e_phnum %d\n", header32->e_phnum);
	printf("e_shentsize %d\n", header32->e_shentsize);
	printf("e_shnum %d\n", header32->e_shnum);
	printf("e_shstrndx %d\n", header32->e_shstrndx);
	Elf64_Ehdr	*header = map;
	printf("e_ident ");
	for (int i = 0; i < EI_NIDENT;i++) {
		printf("%c", header->e_ident[i]);
	}
	printf("\n\n");
	printf("e_type %d\n", header->e_type);
	printf("e_machine %d\n", header->e_machine);
	printf("e_version %d\n", header->e_version);
	printf("e_entry %ld\n", header->e_entry);
	printf("e_phoff %ld\n", header->e_phoff);
	printf("e_shoff %ld\n", header->e_shoff);
	printf("e_flags %d\n", header->e_flags);
	printf("e_ehsize %d\n", header->e_ehsize);
	printf("e_phentsize %d\n", header->e_phentsize);
	printf("e_phnum %d\n", header->e_phnum);
	printf("e_shentsize %d\n", header->e_shentsize);
	printf("e_shnum %d\n", header->e_shnum);
	printf("e_shstrndx %d\n\n", header->e_shstrndx);
}

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		print_prg(argv[0], NULL, ERR_NO_PRG);
		return 1;
	}
	int	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		print_prg(argv[0], NULL, NULL);
		return 1;
	}
	struct stat	my_stat = {0};
	if (stat(argv[1], &my_stat) != 0) {
		print_prg(argv[0], "stat", NULL);
		return 1;
	}
	size_t	len = my_stat.st_size;
	printf("size tot %zu\n", len);
	// char *tab = malloc(len);
	// read(fd, tab, len);
	// write(1, tab, len);
	// free(tab);
	// return ;
	printf("file size %zu\n", len);
	size_t	offset = 0;
	void	*map = mmap(NULL, len - offset, PROT_EXEC, MAP_PRIVATE, fd, offset);
	if (map == (void *) -1) {
		print_prg(argv[0], "mmap", NULL);
		return 1;
	}
	print_header(map);
	Elf64_Ehdr* elfHeader = (Elf64_Ehdr*)map;
    if (elfHeader->e_ident[EI_MAG0] != ELFMAG0 ||
        elfHeader->e_ident[EI_MAG1] != ELFMAG1 ||
        elfHeader->e_ident[EI_MAG2] != ELFMAG2 ||
        elfHeader->e_ident[EI_MAG3] != ELFMAG3 ||
        elfHeader->e_ident[EI_CLASS] != ELFCLASS64 ||
        elfHeader->e_ident[EI_DATA] != ELFDATA2LSB /*||
        elfHeader->e_type != ET_EXEC*/) {
        fprintf(stderr, "Invalid or unsupported ELF format.\n");
        munmap(map, len);
        close(fd);
        return 1;
    }
	// recup ptr 1er hdr section
	printf("section header offset %d\n",elfHeader->e_shoff );
	Elf64_Shdr* sectionHeaders = (Elf64_Shdr*)((char*)map + elfHeader->e_shoff);
    Elf64_Shdr* symbolTableHeader = NULL;
    Elf64_Shdr* stringTableHeader = NULL;
	printf("nb section %d\n", elfHeader->e_shnum);
	// parcourt hdr section
    for (int i = 0; i < elfHeader->e_shnum; i++) {
        if (sectionHeaders[i].sh_type == SHT_SYMTAB) {
            symbolTableHeader = &sectionHeaders[i];
        } else if (sectionHeaders[i].sh_type == SHT_STRTAB) {
            stringTableHeader = &sectionHeaders[i];
        }

        if (symbolTableHeader != NULL && stringTableHeader != NULL) {
            break;
        }
    }

    if (symbolTableHeader == NULL || stringTableHeader == NULL) {
        fprintf(stderr, "Symbol table or string table not found.\n");
        munmap(map, len);
        close(fd);
        return 1;
    }

    //Get the symbol table and string table pointers.
    Elf64_Sym* symbols = (Elf64_Sym*)(map + symbolTableHeader->sh_offset);
    const char* strTable = (const char*)(map + stringTableHeader->sh_offset);

    // Iterate through the symbol table and print symbol information.
    printf("Symbol table:\n");
    for (int i = 0; i < symbolTableHeader->sh_size / sizeof(Elf64_Sym); ++i) {
        printf("%016lx %s\n", (unsigned long long)symbols[i].st_value, &strTable[symbols[i].st_name]) ;
    }
	// Elf64_Ehdr	*header = (Elf64_Ehdr	*) map;
	// Elf64_Shdr	*section_header = (Elf64_Shdr*)((char	*)map + header->e_shoff);
	// printf("%p %p\n", section_header, map + len - offset);
	// while (section_header < map + len - offset) {
	// 	if (section_header->sh_type == SHT_DYNSYM || section_header->sh_type == SHT_SYMTAB) {
	// 		printf("section name %s\n", (char*)map + section_header->sh_name);
	// 		printf("\ttype %d\n", section_header->sh_type);
	// 		printf("\toffset %d\n", section_header->sh_offset);
	// 		printf("\tsize %d\n", section_header->sh_size);
	// 		// Elf64_Sym *section = section_header->sh_addr;
	// 		// while ((char*)section <= map + section_header->sh_offset + section_header->sh_size+sizeof(Elf64_Sym)) {
	// 		// 	printf("\t\t%p sym %s\n", section, map + section_header->sh_offset + section->st_name);
	// 		// 	++section;
	// 		// }
	// 		// printf("\n");
	// 	}
	// 	++section_header;
	// }
	//write(1, map, len);
	if (munmap(map, len)) {
		print_prg(argv[0], "munmap", NULL);
		return 1;
	}
	close(fd);
	return 0;
}

