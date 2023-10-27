/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:51:18 by aartiges          #+#    #+#             */
/*   Updated: 2023/10/27 15:12:45 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H

# define LIB_H

# include "../utils/struct.h"
# include "../utils/utils.h"
# include <stdlib.h>

/*******************************************/
/**************** General ******************/
/*******************************************/

int			ft_get_global_infos(t_nm *nm);

/*******************************************/
/**************** 64-bits ******************/
/*******************************************/

int			ft_nm_64(t_nm *nm);
void		ft_print_64(t_nm *nm, int index);

Elf64_Shdr	*ft_get_section_hdr_64(t_nm *nm, Elf64_Half i_table);
int			ft_get_section_hdrs_64(t_nm *nm);
int			ft_get_elf_hdr_infos_64(t_nm *nm);
// section
void		*ft_get_section_content_64(
				t_nm *nm,
				const Elf64_Shdr *hdr);
void		ft_clean_nm_64(t_symbol_64 *syms);
void		ft_list_sym_add_64(t_nm *nm, t_symbol_64 *sym);
size_t		ft_list_size_64(t_symbol_64 *lst);
void		ft_list_sort_64(t_nm *nm);

char		ft_symbol_get_type_64(t_nm *nm, const t_Sym_64 *sym, char *name);
char		*ft_symbol_get_name_64(
				t_nm *nm,
				const t_S_hdr_64 *hdr,
				const t_Sym_64 *sym);

Elf64_Phdr	*ft_get_prg_hdr_64(t_nm *nm, Elf64_Half i_table);

/*******************************************/
/**************** 32-bits ******************/
/*******************************************/

int			ft_nm_32(t_nm *nm);
void		ft_print_32(t_nm *nm, int index);

Elf32_Shdr	*ft_get_section_hdr_32(t_nm *nm, Elf32_Half i_table);
int			ft_get_section_hdrs_32(t_nm *nm);
int			ft_get_elf_hdr_infos_32(t_nm *nm);
// section
void		*ft_get_section_content_32(
				t_nm *nm,
				const Elf32_Shdr *hdr);
void		ft_clean_nm_32(t_symbol_32 *syms);
void		ft_list_sym_add_32(t_nm *nm, t_symbol_32 *sym);
size_t		ft_list_size_32(t_symbol_32 *lst);
void		ft_list_sort_32(t_nm *nm);
char		ft_symbol_get_type_32(t_nm *nm, const t_Sym_32 *sym, char *name);
char		*ft_symbol_get_name_32(
				t_nm *nm,
				const t_S_hdr_32 *hdr,
				const t_Sym_32 *sym);

Elf32_Phdr	*ft_get_prg_hdr_32(t_nm *nm, Elf32_Half i_table);

#endif
