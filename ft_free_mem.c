/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:47:57 by tbondare          #+#    #+#             */
/*   Updated: 2019/08/28 20:06:11 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftlemin.h"

void	del_el_val_path(t_vld_path_elem *frs_el)
{
	t_vld_path_elem *crn_fst_el;

	while (frs_el)
	{
		crn_fst_el = frs_el->next;
		free(frs_el);
		frs_el = crn_fst_el;
	}
}

void	del_rm_lnks(t_links *rm_lnk)
{
	t_links *mem_rm_lnk;

	while (rm_lnk)
	{
		mem_rm_lnk = rm_lnk->next;
		free(rm_lnk);
		rm_lnk = mem_rm_lnk;
	}
}

void	del_rm_from(t_ls_come_from *from)
{
	t_ls_come_from *mem_frm;

	while (from)
	{
		mem_frm = from->next;
		free(from);
		from = mem_frm;
	}
}

void	free_mem(t_input_data *data)
{
	t_list_rooms *crn_rm;
	t_list_tubes *crn_tbs;

	while (data->frst_rm)
	{
		crn_rm = data->frst_rm->next_rm;
		del_rm_from(data->frst_rm->from);
		del_rm_lnks(data->frst_rm->link);
		free(data->frst_rm->name);
		free(data->frst_rm);
		data->frst_rm = crn_rm;
	}
	while (data->frst_tb)
	{
		crn_tbs = data->frst_tb->next_tb;
		free(data->frst_tb->first);
		free(data->frst_tb->second);
		free(data->frst_tb);
		data->frst_tb = crn_tbs;
	}
}

void	free_mem_val_path(t_lst_vld_path *lst_vld_path)
{
	t_lst_vld_path *frs_el;

	while (lst_vld_path)
	{
		frs_el = lst_vld_path->next;
		del_el_val_path(lst_vld_path->frst_path_el);
		free(lst_vld_path);
		lst_vld_path = frs_el;
	}
}
