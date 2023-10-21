#include "lib.h"
#include <stdio.h>

void	print_sym_64(Elf64_Sym *sym, char *str_tab, t_binary_64 *bin)
{
	const u_int8_t	visibility = ELF64_ST_VISIBILITY(sym->st_other);
	const u_int8_t	type = ELF64_ST_TYPE(sym->st_info);
	const u_int8_t	bind = ELF64_ST_BIND(sym->st_info);
	const u_int16_t	shndx = swap_uint16(sym->st_shndx, bin->endian);
	const char		*name = str_tab + swap_uint32(sym->st_name, bin->endian);
	char			c;
	u_int8_t		debug = 0;

	if ((type == STT_NOTYPE && bind == STB_LOCAL && visibility == STV_DEFAULT && shndx == SHN_UNDEF) || shndx == SHN_ABS)
		c = print_type('a', bind == STB_GLOBAL);
	else if (type == STT_OBJECT && bind == STB_WEAK)
		c = print_type('v', shndx != SHN_UNDEF);
	else if (bind == STB_WEAK)
		c = print_type('w', shndx != SHN_UNDEF);
	else if (shndx != SHN_ABS && shndx != SHN_COMMON && shndx != SHN_UNDEF && shndx != SHN_XINDEX)
	{
		Elf64_Shdr	*hdr = get_n_section_header_64(bin, shndx);
		u_int64_t	sh_flags = swap_uint64(hdr->sh_flags, bin->endian);
		u_int64_t	sh_type = swap_uint32(hdr->sh_type, bin->endian);
		if (type == STT_SECTION)
			name = bin->shstrtab + swap_uint32(hdr->sh_name, bin->endian);
		if (sh_type == SHT_NOBITS)
			c = print_type('b', bind == STB_GLOBAL);
		else if (sh_type == SHT_PROGBITS && (sh_flags == (SHF_ALLOC | SHF_EXECINSTR) || sh_flags == (SHF_ALLOC | SHF_EXECINSTR | SHF_WRITE)))
			c = print_type('t', bind == STB_GLOBAL);
		else if (type == STT_SECTION && ft_strncmp(name, DEBUG_SECTION, ft_strlen(DEBUG_SECTION)) == 0)
			c = print_type('N', 0);
		else if ((sh_type == SHT_PROGBITS || sh_type == SHT_INIT_ARRAY || sh_type == SHT_FINI_ARRAY || sh_type == SHT_DYNAMIC)
			&& sh_flags == (SHF_WRITE | SHF_ALLOC))
			c = print_type('d', bind == STB_GLOBAL);
		else if (sh_flags & SHF_ALLOC)
			c = print_type('r', bind == STB_GLOBAL);
		else if (type == STT_SECTION && (sh_type == SHT_SYMTAB || sh_type == SHT_STRTAB))
			c = print_type('a', bind == STB_GLOBAL);
		else if (type == STT_SECTION)
			c = print_type('n', 0);
		else
		{
			c = print_type('?', 0);
			c = print_type('?', 0);
			debug = 1;
		}
	}
	else if (shndx == SHN_UNDEF)
		c = print_type('U', 0);
	else
	{
		c = print_type('?', 0);
		//debug = 1;
	}

	Elf64_Addr	val = swap_uint64(sym->st_value, bin->endian);
	if (val && c != 'U' && c != 'w')
		print_number_n_digit(val, 16);
	else if (
		(type == STT_NOTYPE && bind == STB_LOCAL && visibility == STV_DEFAULT && shndx == SHN_UNDEF)
		|| shndx == SHN_ABS || type == STT_SECTION)
		print_number_n_digit(0, 16);
	else
		write(1, "                ", 16);
	write(1, SEP_SPACE, 1);
	write(1, &c, 1);
	write(1, SEP_SPACE, 1);
	write(1, name, ft_strlen(name));
	write(1, SEP_NL, 1);

	// if (val == 0x00011b20)
	// 	debug = 1;
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
			shndx == SHN_ABS	? "ABS   " :
			shndx == SHN_COMMON	? "COMMON" :// c C
			shndx == SHN_UNDEF	? "UNDEF " :
			shndx == SHN_XINDEX	? "XINDEX" :
										"?     ", //b (section = .bss); d (section = .data); t (section = .text)
			shndx
		);
		if (shndx != SHN_ABS && shndx != SHN_COMMON && shndx != SHN_UNDEF && shndx != SHN_XINDEX)
		{
			Elf64_Shdr	*hdr = get_n_section_header_64(bin, shndx);
			u_int64_t	sh_flags = swap_uint64(hdr->sh_flags, bin->endian);
			u_int64_t	sh_type = swap_uint64(hdr->sh_type, bin->endian);
			printf("\t\t%s\n\t\ttypes: %s\n\t\tflags: %s%s%s%s%s%s%s%s%s%s%s%s%s%s\n\t\tlink %d\n",
				bin->shstrtab + swap_uint64(hdr->sh_name, bin->endian),
				sh_type == SHT_NULL ?			"Section header table entry unused" :
				sh_type == SHT_PROGBITS ?		"Program data                     " :
				sh_type == SHT_SYMTAB ?		"Symbol table                     " :
				sh_type == SHT_STRTAB ?		"String table                     " :
				sh_type == SHT_RELA ?			"Relocation entries with addends  " :
				sh_type == SHT_HASH ?			"Symbol hash table                " :
				sh_type == SHT_DYNAMIC ?		"Dynamic linking information      " :
				sh_type == SHT_NOTE ?			"Notes                            " :
				sh_type == SHT_NOBITS ?		"Program space with no data (bss) " :
				sh_type == SHT_REL ?			"Relocation entries, no addends   " :
				sh_type == SHT_SHLIB ?			"Reserved                         " :
				sh_type == SHT_DYNSYM ?		"Dynamic linker symbol table      " :
				sh_type == SHT_INIT_ARRAY ?	"Array of constructors            " :
				sh_type == SHT_FINI_ARRAY ?	"Array of destructors             " :
				sh_type == SHT_PREINIT_ARRAY ?	"Array of pre-constructors        " :
				sh_type == SHT_GROUP ?			"Section group                    " :
				sh_type == SHT_SYMTAB_SHNDX ?	"Extended section indices         " :
				sh_type == SHT_NUM ?			"Number of defined types          " :
				sh_type == SHT_LOOS ?			"Start OS-specific                " :
													"Other                            ",
				sh_flags & SHF_WRITE ? "Writable " : "",
				sh_flags & SHF_ALLOC ? "Occupies memory during execution " : "",
				sh_flags & SHF_EXECINSTR ? "Executable " : "",
				sh_flags & SHF_MERGE ? "Might be merged " : "",
				sh_flags & SHF_STRINGS ? "Contains null-terminated strings " : "",
				sh_flags & SHF_INFO_LINK ? "'sh_info' contains SHT index " : "",
				sh_flags & SHF_LINK_ORDER ? "Preserve order after combining " : "",
				sh_flags & SHF_OS_NONCONFORMING ? "Non-standard OS specific handling required " : "",
				sh_flags & SHF_GROUP ? "Section is member of a group " : "",
				sh_flags & SHF_TLS ? "Section hold thread-local data " : "",
				sh_flags & SHF_MASKOS ? "OS-specific " : "",
				sh_flags & SHF_MASKPROC ? "Processor-specific " : "",
				sh_flags & SHF_ORDERED ? "Special ordering requirement (Solaris) " : "",
				sh_flags & SHF_EXCLUDE ? "Section is excluded unless referenced or allocated (Solaris) " : "",
				swap_uint32(hdr->sh_link, bin->endian)
			);
		}
	}
}
