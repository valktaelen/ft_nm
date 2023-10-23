#include "../lib.h"

void	ft_clean_nm_32(t_symbol_32 *syms)
{
	t_symbol_32	*sym;

	while (syms)
	{
		sym = syms;
		syms = syms->next;
		free(sym);
	}
}

void	ft_list_sym_add_32(t_nm *nm, t_symbol_32 *sym)
{
	if (nm->bin_32.syms)
		sym->next = nm->bin_32.syms;
	else
		sym->next = NULL;
	nm->bin_32.syms = sym;
}
