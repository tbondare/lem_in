/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:56:51 by tbondare          #+#    #+#             */
/*   Updated: 2019/09/27 18:31:20 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"

void	inner_whl_f_run_ants(t_vld_path_elem *crnt_el,
		t_output_data *out, int *j)
{
	int i;

	i = crnt_el->i;
	while (crnt_el)
	{
		out->arr_paths[i].path[*j].name = crnt_el->room->name;
		out->arr_paths[i].path[*j].ant_index = 0;
		crnt_el = crnt_el->next;
		(*j)++;
	}
}

void	cnt_ants_for_each_path(t_lst_vld_path *lst_vld_path,
		int data_ants, int x, int cnt_paths)
{
	int				cnt;
	int				sum_ants;
	t_lst_vld_path	*crnt_path;

	cnt = 0;
	sum_ants = 0;
	crnt_path = lst_vld_path;
	while (cnt < cnt_paths)
	{
		crnt_path->x = x - crnt_path->leng;
		sum_ants = sum_ants + crnt_path->x;
		crnt_path = crnt_path->next;
		cnt++;
	}
	sum_ants = data_ants - sum_ants;
	crnt_path = lst_vld_path;
	while (crnt_path && sum_ants > 0)
	{
		crnt_path->x++;
		sum_ants--;
		crnt_path = crnt_path->next;
	}
}

int		distribute_ants_to_paths(t_input_data *data,
		t_lst_vld_path *lst_vld_path)
{
	int				x;
	int				sum_d;
	int				cnt_paths;
	t_lst_vld_path	*crnt_val_path;

	x = 0;
	cnt_paths = 1;
	crnt_val_path = lst_vld_path;
	sum_d = lst_vld_path->leng;
	while (crnt_val_path)
	{
		x = (sum_d + data->cnt_ants) / cnt_paths;
		if (crnt_val_path->next == NULL || crnt_val_path->next->leng > x)
			break ;
		cnt_paths++;
		crnt_val_path = crnt_val_path->next;
		sum_d = sum_d + crnt_val_path->leng;
	}
	cnt_ants_for_each_path(lst_vld_path, data->cnt_ants, x, cnt_paths);
	return (cnt_paths);
}

void while_for_run_ants(t_input_data *data, t_output_data *out,t_lst_vld_path *crnt)
{
	int				i;
	int				j;
	t_vld_path_elem	*crnt_el;

	i = 0;
	while (crnt && out->nmb_paths > i)
	{
		crnt_el = crnt->frst_path_el;
		out->arr_paths[i].path =
				(t_out_room*)malloc(sizeof(t_out_room) * crnt->leng);
		j = 0;
		if (crnt->leng > 1)
		{
			crnt_el->i = i;
			inner_whl_f_run_ants(crnt_el, out, &j);
		}
		else
			print_ants_in_one_line(data->cnt_ants, data->end_room_name);
		out->arr_paths[i].nmb_ants = crnt->x;
		out->arr_paths[i].path_leng = crnt->leng;
		out->arr_paths[i].path[j].name = data->end_room_name;
		out->arr_paths[i].path[j].ant_index = 0;
		i++;
		crnt = crnt->next;
	}
}

void	run_ants(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
	t_output_data	out;
	t_lst_vld_path	*crnt;

	crnt = lst_vld_path;
	out.nmb_paths = distribute_ants_to_paths(data, lst_vld_path);
	out.arr_paths = (t_out_path*)malloc(sizeof(t_out_path) * out.nmb_paths);
	while_for_run_ants(data, &out, crnt);
	output_ants(data, &out);
	del_arr_path(&out);
}
