#include "../lib.h"

void	ft_print_32(t_nm *nm, int index)
{
	t_symbol_32	*sym;

	sym = nm->bin_32.syms;
	if (!sym)
	{
		print_prg_error(nm, INFO_NO_SYM);
		return ;
	}
	if (index)
	{
		write(1, SEP_NL, 1);
		write(1, nm->file_path, ft_strlen(nm->file_path));
		write(1, SEP_1, 1);
		write(1, SEP_NL, 1);
	}
	while (sym)
	{
		if (sym->type != 'U' && sym->type != 'w')
			print_number_n_digit(sym->st_value, 8);
		else if (
			(sym->info_type == STT_NOTYPE && sym->bind == STB_LOCAL && sym->visibility == STV_DEFAULT && sym->st_shndx == SHN_UNDEF)
			|| sym->st_shndx == SHN_ABS || sym->info_type == STT_SECTION)
			print_number_n_digit(0, 8);
		else
			write(1, "        ", 8);
		write(1, SEP_SPACE, 1);
		write(1, &sym->type, 1);
		write(1, SEP_SPACE, 1);
		write(1, sym->name, ft_strlen(sym->name));
		write(1, SEP_NL, 1);
		sym = sym->next;
	}
}
