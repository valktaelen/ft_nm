#include "lib.h"
#include <stdio.h>

void	print_elf_header_64(Elf64_Ehdr *hdr)
{
	printf("ELF header:\n");
	printf("\tMagic number: %x %c%c%c\n",
		hdr->e_ident[EI_MAG0],
		hdr->e_ident[EI_MAG1],
		hdr->e_ident[EI_MAG2],
		hdr->e_ident[EI_MAG3]
	);
	printf("\tARCH: %s\n", hdr->e_ident[EI_CLASS] == 1 ? "32-bit" : "64-bit");
	printf("\tEndian: %s\n", hdr->e_ident[EI_DATA] == 1 ? "little" : "big");
	printf("\tOriginal or current version of elf: %s\n", hdr->e_ident[EI_VERSION] == 1 ? "true": "false");
	u_int8_t	os = hdr->e_ident[EI_OSABI];
	printf("\tTarget OS: %s\n", os == 0 ? "System V" :
		(
			os == 3 ? "Linux" : "Other"
		)
	);
	u_int16_t	type = hdr->e_type;
	printf("\tType: %s\n",
		type == ET_NONE ? "Unknow" :
		type == ET_REL ? "Relocatable file" :
		type == ET_EXEC ? "Executable file" :
		type == ET_DYN ? "Shared object" :
		type == ET_CORE ? "Core file" :
		"Other"
	);
	printf("\tOriginal version of ELF: %s\n", hdr->e_version == 1 ? "true" : "false");
	printf("\tOffset program header: %zu\n", hdr->e_phoff);
	printf("\tOffset section headers: %zu\n", hdr->e_shoff);
	printf("\tnumber of entries in the section header table: %d\n", hdr->e_shnum);
}

void	print_prg_header_64(Elf64_Phdr *hdr)
{
	printf("Program header:\n");
	u_int32_t	type = hdr->p_type;
	printf("\tType: %s\n",
		type == PT_NULL ? "Program header table entry unused" :
		type == PT_LOAD ? "Loadable segment" :
		type == PT_DYNAMIC ? "Dynamic linking information" :
		type == PT_INTERP ? "Interpreter information" :
		type == PT_NOTE ? "Auxiliary information" :
		type == PT_SHLIB ? "Reserved" :
		type == PT_PHDR ? "	Segment containing program header table itself" :
		type == PT_TLS ? "	Thread-Local Storage template" :
		"Other"
	);
	printf("\tFlags: %s %s %s\n",
		hdr->p_flags & PF_X ? "Executable segment" : "",
		hdr->p_flags & PF_W ? "Writeable segment" : "",
		hdr->p_flags & PF_R ? "Readable segment" : ""
	);
}

void	print_section_header_64(Elf64_Shdr *hdr, char *shstrtab)
{
	printf("Section table %s\n", shstrtab + hdr->sh_name);
	printf("\tType: %s\n",
		hdr->sh_type == SHT_NULL ? "Section header table entry unused" :
		hdr->sh_type == SHT_PROGBITS ? "Program data" :
		hdr->sh_type == SHT_SYMTAB ? "Symbol table" :
		hdr->sh_type == SHT_STRTAB ? "String table" :
		hdr->sh_type == SHT_RELA ? "Relocation entries with addends" :
		hdr->sh_type == SHT_HASH ? "Symbol hash table" :
		hdr->sh_type == SHT_DYNAMIC ? "Dynamic linking information" :
		hdr->sh_type == SHT_NOTE ? "Notes" :
		hdr->sh_type == SHT_NOBITS ? "Program space with no data (bss)" :
		hdr->sh_type == SHT_REL ? "Relocation entries, no addends" :
		hdr->sh_type == SHT_SHLIB ? "Reserved" :
		hdr->sh_type == SHT_DYNSYM ? "Dynamic linker symbol table" :
		hdr->sh_type == SHT_INIT_ARRAY ? "Array of constructors" :
		hdr->sh_type == SHT_FINI_ARRAY ? "Array of destructors" :
		hdr->sh_type == SHT_PREINIT_ARRAY ? "Array of pre-constructors" :
		hdr->sh_type == SHT_GROUP ? "Section group" :
		hdr->sh_type == SHT_SYMTAB_SHNDX ? "Extended section indices" :
		hdr->sh_type == SHT_NUM ? "Number of defined types" :
		hdr->sh_type == SHT_LOOS ? "Start OS-specific" :
		"Other"
	);
	printf("\tFlags: %s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		hdr->sh_flags & SHF_WRITE ? "Writable " : "",
		hdr->sh_flags & SHF_ALLOC ? "Occupies memory during execution " : "",
		hdr->sh_flags & SHF_EXECINSTR ? "Executable " : "",
		hdr->sh_flags & SHF_MERGE ? "Might be merged " : "",
		hdr->sh_flags & SHF_STRINGS ? "Contains null-terminated strings " : "",
		hdr->sh_flags & SHF_INFO_LINK ? "'sh_info' contains SHT index " : "",
		hdr->sh_flags & SHF_LINK_ORDER ? "Preserve order after combining " : "",
		hdr->sh_flags & SHF_OS_NONCONFORMING ? "Non-standard OS specific handling required " : "",
		hdr->sh_flags & SHF_GROUP ? "Section is member of a group " : "",
		hdr->sh_flags & SHF_TLS ? "Section hold thread-local data " : "",
		hdr->sh_flags & SHF_MASKOS ? "OS-specific " : "",
		hdr->sh_flags & SHF_MASKPROC ? "Processor-specific " : "",
		hdr->sh_flags & SHF_ORDERED ? "Special ordering requirement (Solaris) " : "",
		hdr->sh_flags & SHF_EXCLUDE ? "Section is excluded unless referenced or allocated (Solaris) " : ""
	);
	printf("\tVirtual address of the section in memory: %ld\n", hdr->sh_addr);
	printf("\tOffset of the section in the file image: %zu\n", hdr->sh_offset);
	printf("\tSize of section: %zu\n", hdr->sh_size);
	printf("\tLink section: %u\n", hdr->sh_link);
}

void	print_number_n_digit(Elf64_Addr n, size_t digit)
{
	static char	*base = "0123456789abcdef";

	while (digit)
		write(1, base + ((n >> (--digit * 4)) % 16), 1);
}

void	print_type(char lower_letter, u_int8_t to_upper)
{
	if (to_upper)
		lower_letter += 'A' - 'a';
	write(1, &lower_letter, 1);
}

void	print_sym_64(Elf64_Sym *sym, char *str_tab, t_binary_64 *bin)
{
	const u_int8_t	visibility = ELF64_ST_VISIBILITY(sym->st_other);
	const u_int8_t	type = ELF64_ST_TYPE(sym->st_info);
	const u_int8_t	bind = ELF64_ST_BIND(sym->st_info);
	const char		*name = str_tab + sym->st_name;
	u_int8_t	debug = 0;

	if (sym->st_value)
		print_number_n_digit(sym->st_value, 16);
	else if ((type == STT_NOTYPE && bind == STB_LOCAL && visibility == STV_DEFAULT && sym->st_shndx == SHN_UNDEF) || sym->st_shndx == SHN_ABS)
		print_number_n_digit(0, 16);
	else
		write(1, "                ", 16);
	write(1, SEP_SPACE, 1);
	if ((type == STT_NOTYPE && bind == STB_LOCAL && visibility == STV_DEFAULT && sym->st_shndx == SHN_UNDEF) || sym->st_shndx == SHN_ABS)
		print_type('a', 0);
	else
	if (type == STT_OBJECT && bind == STB_WEAK)
		print_type('v', sym->st_shndx != SHN_UNDEF);
	else if (bind == STB_WEAK)
		print_type('w', sym->st_shndx != SHN_UNDEF);
	else if (sym->st_shndx != SHN_ABS && sym->st_shndx != SHN_COMMON && sym->st_shndx != SHN_UNDEF && sym->st_shndx != SHN_XINDEX)
	{
		Elf64_Shdr	*hdr = get_n_section_header_64(bin, sym->st_shndx);
		if (hdr->sh_type == SHT_PROGBITS && hdr->sh_flags == SHF_ALLOC)
			print_type('r', bind == STB_GLOBAL);
		else if (hdr->sh_type == SHT_NOBITS)
			print_type('b', bind == STB_GLOBAL);
		else if (hdr->sh_type == SHT_PROGBITS && hdr->sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
			print_type('t', bind == STB_GLOBAL);
		else if ((hdr->sh_type == SHT_PROGBITS || hdr->sh_type == SHT_INIT_ARRAY || hdr->sh_type == SHT_FINI_ARRAY || hdr->sh_type == SHT_DYNAMIC)
			&& hdr->sh_flags == (SHF_WRITE | SHF_ALLOC))
			print_type('d', bind == STB_GLOBAL);
		else
			debug = 1;
	}
	else if (sym->st_shndx == SHN_UNDEF)
		print_type('U', 0);
	else
	{
		print_type('?', 0);
		debug = 1;
	}


	write(1, SEP_SPACE, 1);
	write(1, name, ft_strlen(name));
	write(1, SEP_NL, 1);

	if (debug)
	{
		printf("%s\n\ttype: %s\n\tbind: %s\n\tvisibility: %s\n\treferto section: %s %u\n",
			name,
			type == STT_NOTYPE	? "NOTYPE " :
			type == STT_OBJECT	? "OBJECT " :
			type == STT_FUNC	? "FUNC   " :
			type == STT_SECTION	? "SECTION" :
			type == STT_FILE	? "FILE   " :
			type == STT_TLS		? "TLS    " :
			type == STT_LOOS	? "LOOS   " :
			type == STT_HIOS	? "HIOS   " :
			type == STT_LOPROC	? "LOPROC " :
			type == STT_HIPROC	? "HIPROC " :
								"?      ",
			bind == STB_LOCAL	? "LOCAL " :
			bind == STB_GLOBAL	? "GLOBAL" :
			bind == STB_WEAK	? "WEAK  " :
			bind == STB_LOOS	? "LOOS  " :
			bind == STB_HIOS	? "HIOS  " :
			bind == STB_LOPROC	? "LOPROC" :
			bind == STB_HIPROC	? "HIPROC" :
								"?     ",
			visibility == STV_DEFAULT	? "DEFAULT  " :
			visibility == STV_INTERNAL	? "INTERNAL " :
			visibility == STV_HIDDEN	? "HIDDEN   " :
			visibility == STV_PROTECTED	? "PROTECTED" :
										"?        ",
			sym->st_shndx == SHN_ABS	? "ABS   " :
			sym->st_shndx == SHN_COMMON	? "COMMON" :// c C
			sym->st_shndx == SHN_UNDEF	? "UNDEF " :
			sym->st_shndx == SHN_XINDEX	? "XINDEX" :
										"?     ", //b (section = .bss); d (section = .data); t (section = .text)
			sym->st_shndx
		);
		if (sym->st_shndx != SHN_ABS && sym->st_shndx != SHN_COMMON && sym->st_shndx != SHN_UNDEF && sym->st_shndx != SHN_XINDEX)
		{
			Elf64_Shdr	*hdr = get_n_section_header_64(bin, sym->st_shndx);
			printf("\t\t%s\n\t\ttypes: %s\n\t\tflags: %s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
				bin->shstrtab + hdr->sh_name,
				hdr->sh_type == SHT_NULL ?			"Section header table entry unused" :
				hdr->sh_type == SHT_PROGBITS ?		"Program data                     " :
				hdr->sh_type == SHT_SYMTAB ?		"Symbol table                     " :
				hdr->sh_type == SHT_STRTAB ?		"String table                     " :
				hdr->sh_type == SHT_RELA ?			"Relocation entries with addends  " :
				hdr->sh_type == SHT_HASH ?			"Symbol hash table                " :
				hdr->sh_type == SHT_DYNAMIC ?		"Dynamic linking information      " :
				hdr->sh_type == SHT_NOTE ?			"Notes                            " :
				hdr->sh_type == SHT_NOBITS ?		"Program space with no data (bss) " :
				hdr->sh_type == SHT_REL ?			"Relocation entries, no addends   " :
				hdr->sh_type == SHT_SHLIB ?			"Reserved                         " :
				hdr->sh_type == SHT_DYNSYM ?		"Dynamic linker symbol table      " :
				hdr->sh_type == SHT_INIT_ARRAY ?	"Array of constructors            " :
				hdr->sh_type == SHT_FINI_ARRAY ?	"Array of destructors             " :
				hdr->sh_type == SHT_PREINIT_ARRAY ?	"Array of pre-constructors        " :
				hdr->sh_type == SHT_GROUP ?			"Section group                    " :
				hdr->sh_type == SHT_SYMTAB_SHNDX ?	"Extended section indices         " :
				hdr->sh_type == SHT_NUM ?			"Number of defined types          " :
				hdr->sh_type == SHT_LOOS ?			"Start OS-specific                " :
													"Other                            ",
				hdr->sh_flags & SHF_WRITE ? "Writable " : "",
				hdr->sh_flags & SHF_ALLOC ? "Occupies memory during execution " : "",
				hdr->sh_flags & SHF_EXECINSTR ? "Executable " : "",
				hdr->sh_flags & SHF_MERGE ? "Might be merged " : "",
				hdr->sh_flags & SHF_STRINGS ? "Contains null-terminated strings " : "",
				hdr->sh_flags & SHF_INFO_LINK ? "'sh_info' contains SHT index " : "",
				hdr->sh_flags & SHF_LINK_ORDER ? "Preserve order after combining " : "",
				hdr->sh_flags & SHF_OS_NONCONFORMING ? "Non-standard OS specific handling required " : "",
				hdr->sh_flags & SHF_GROUP ? "Section is member of a group " : "",
				hdr->sh_flags & SHF_TLS ? "Section hold thread-local data " : "",
				hdr->sh_flags & SHF_MASKOS ? "OS-specific " : "",
				hdr->sh_flags & SHF_MASKPROC ? "Processor-specific " : "",
				hdr->sh_flags & SHF_ORDERED ? "Special ordering requirement (Solaris) " : "",
				hdr->sh_flags & SHF_EXCLUDE ? "Section is excluded unless referenced or allocated (Solaris) " : ""
			);


		}
	}
}
