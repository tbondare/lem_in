/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:29:54 by tbondare          #+#    #+#             */
/*   Updated: 2019/08/31 16:43:03 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"

t_list_rooms	*found_ptr_room_by_name(t_input_data *data, char *name)
{
	t_list_rooms *crnt_rm;

	crnt_rm = data->frst_rm;
	while (crnt_rm)
	{
		if (ft_strequ(crnt_rm->name, name) == 1)
			return (crnt_rm);
		crnt_rm = crnt_rm->next_rm;
	}
	return (0);
}

int				is_same_link(t_links *lnk, char *name)
{
	t_links *crn_lnk;

	crn_lnk = lnk;
	while (crn_lnk)
	{
		if (ft_strequ(crn_lnk->linked_room->name, name) == 1)
			return (1);
		crn_lnk = crn_lnk->next;
	}
	return (0);
}

void			helper_f_add_tbs(t_input_data *data, t_list_tubes *frs_tb,
		t_list_rooms **crnt_rm)
{
	char	*b;
	t_links	*oldlnk;

	oldlnk = NULL;
	while (frs_tb)
	{
		if (ft_strequ((*crnt_rm)->name, frs_tb->first) == 1)
			b = frs_tb->second;
		else if (ft_strequ((*crnt_rm)->name, frs_tb->second) == 1)
			b = frs_tb->first;
		else
		{
			frs_tb = frs_tb->next_tb;
			continue;
		}
		oldlnk = (*crnt_rm)->link;
		(*crnt_rm)->link = (t_links *)malloc(sizeof(t_links));
		(*crnt_rm)->link->linked_room = found_ptr_room_by_name(data, b);
		(*crnt_rm)->link->next = oldlnk;
		frs_tb = frs_tb->next_tb;
	}
}

void			add_tubes_to_rooms(t_input_data *data)
{
	t_list_rooms *crnt_rm;
	t_list_tubes *frs_tb;

	frs_tb = NULL;
	crnt_rm = data->frst_rm;
	while (crnt_rm)
	{
		frs_tb = data->frst_tb;
		helper_f_add_tbs(data, frs_tb, &crnt_rm);
		crnt_rm = crnt_rm->next_rm;
	}
}

int				main(void)
{
	t_input_data	data;
	t_lst_vld_path	*lst_vld_path;

	data.frst_rm = NULL;
	data.frst_tb = NULL;
	data.cnt_ants = -1;
	if (ft_read_data(&data) == -1 || data.cnt_ants == -1)
	{
		free_mem(&data);
		ft_printf("Failed to read data: ants quantity not found\n");
		exit(0);
	}
	add_tubes_to_rooms(&data);
	lst_vld_path = find_valid_path(&data);
	if (lst_vld_path == NULL)
	{
		free_mem(&data);
		ft_printf("Valid paths didn't found\n");
		exit(1);
	}
	run_ants(&data, lst_vld_path);
	free_mem_val_path(lst_vld_path);
	free_mem(&data);
	return (0);
}
