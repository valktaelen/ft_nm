#include "lib.h"
#include <stdio.h>

void	print_elf_header_32(Elf32_Ehdr *hdr)
{
	const u_int16_t	type = swap_uint32(hdr->e_type, hdr->e_ident[EI_DATA]);
	printf("ELF header:\n");
	printf("\tMagic number: %x %c%c%c\n",
		hdr->e_ident[EI_MAG0],
		hdr->e_ident[EI_MAG1],
		hdr->e_ident[EI_MAG2],
		hdr->e_ident[EI_MAG3]
	);
	printf("\tARCH: %s\n", hdr->e_ident[EI_CLASS] == FT_32 ? "32-bit" : "64-bit");
	printf("\tEndian: %s\n", hdr->e_ident[EI_DATA] == FT_LITTLE_ENDIAN ? "little" : "big");
	printf("\tOriginal or current version of elf: %s\n", hdr->e_ident[EI_VERSION] == 1 ? "true": "false");
	printf("\tType: %s\n",
		type == ET_NONE ? "Unknow" :
		type == ET_REL ? "Relocatable file" :
		type == ET_EXEC ? "Executable file" :
		type == ET_DYN ? "Shared object" :
		type == ET_CORE ? "Core file" :
		"Other"
	);
	printf("\tOriginal version of ELF: %s\n", hdr->e_version == 1 ? "true" : "false");
	printf("\tOffset program header: %u\n", swap_uint32(hdr->e_phoff, hdr->e_ident[EI_DATA]));
	printf("\tOffset section headers: %u\n", swap_uint32(hdr->e_shoff, hdr->e_ident[EI_DATA]));
	printf("\tnumber of entries in the section header table: %d\n", swap_uint16(hdr->e_shnum, hdr->e_ident[EI_DATA]));
}

void	print_prg_header_32(Elf32_Phdr *hdr, u_int8_t endian)
{
	const u_int32_t	type = swap_uint32(hdr->p_type, endian);
	const u_int32_t	flag = swap_uint32(hdr->p_flags, endian);

	printf("Program header:\n");
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
		flag & PF_X ? "Executable segment" : "",
		flag & PF_W ? "Writeable segment" : "",
		flag & PF_R ? "Readable segment" : ""
	);
}

void	print_section_header_32(Elf32_Shdr *hdr, char *shstrtab, u_int8_t endian)
{
	const u_int32_t	type = swap_uint32(hdr->sh_type, endian);
	const u_int32_t	flag = swap_uint32(hdr->sh_flags, endian);

	printf("Section table %s\n", shstrtab + hdr->sh_name);
	printf("\tType: %s\n",
		type == SHT_NULL ? "Section header table entry unused" :
		type == SHT_PROGBITS ? "Program data" :
		type == SHT_SYMTAB ? "Symbol table" :
		type == SHT_STRTAB ? "String table" :
		type == SHT_RELA ? "Relocation entries with addends" :
		type == SHT_HASH ? "Symbol hash table" :
		type == SHT_DYNAMIC ? "Dynamic linking information" :
		type == SHT_NOTE ? "Notes" :
		type == SHT_NOBITS ? "Program space with no data (bss)" :
		type == SHT_REL ? "Relocation entries, no addends" :
		type == SHT_SHLIB ? "Reserved" :
		type == SHT_DYNSYM ? "Dynamic linker symbol table" :
		type == SHT_INIT_ARRAY ? "Array of constructors" :
		type == SHT_FINI_ARRAY ? "Array of destructors" :
		type == SHT_PREINIT_ARRAY ? "Array of pre-constructors" :
		type == SHT_GROUP ? "Section group" :
		type == SHT_SYMTAB_SHNDX ? "Extended section indices" :
		type == SHT_NUM ? "Number of defined types" :
		type == SHT_LOOS ? "Start OS-specific" :
		"Other"
	);
	printf("\tFlags: %s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		flag & SHF_WRITE ? "Writable " : "",
		flag & SHF_ALLOC ? "Occupies memory during execution " : "",
		flag & SHF_EXECINSTR ? "Executable " : "",
		flag & SHF_MERGE ? "Might be merged " : "",
		flag & SHF_STRINGS ? "Contains null-terminated strings " : "",
		flag & SHF_INFO_LINK ? "'sh_info' contains SHT index " : "",
		flag & SHF_LINK_ORDER ? "Preserve order after combining " : "",
		flag & SHF_OS_NONCONFORMING ? "Non-standard OS specific handling required " : "",
		flag & SHF_GROUP ? "Section is member of a group " : "",
		flag & SHF_TLS ? "Section hold thread-local data " : "",
		flag & SHF_MASKOS ? "OS-specific " : "",
		flag & SHF_MASKPROC ? "Processor-specific " : "",
		flag & SHF_ORDERED ? "Special ordering requirement (Solaris) " : "",
		flag & SHF_EXCLUDE ? "Section is excluded unless referenced or allocated (Solaris) " : ""
	);
	printf("\tVirtual address of the section in memory: %d\n", swap_uint32(hdr->sh_addr, endian));
	printf("\tOffset of the section in the file image: %u\n", swap_uint32(hdr->sh_offset, endian));
	printf("\tSize of section: %u\n", swap_uint32(hdr->sh_size, endian));
	printf("\tLink section: %u\n", swap_uint32(hdr->sh_link, endian));
}
