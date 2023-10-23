#include "../lib.h"

void	ft_clean_nm_64(t_symbol_64 *syms)
{
	t_symbol_64	*sym;

	while (syms)
	{
		sym = syms;
		syms = syms->next;
		free(sym);
	}
}

void	ft_list_sym_add_64(t_nm *nm, t_symbol_64 *sym)
{
	if (nm->bin_64.syms)
		sym->next = nm->bin_64.syms;
	else
		sym->next = NULL;
	nm->bin_64.syms = sym;
}
