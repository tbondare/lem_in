/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:56:51 by tbondare          #+#    #+#             */
/*   Updated: 2019/09/03 16:07:07 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"

int		print_ants(t_output_data *out)
{
	int i;
	int j;
	int flg;

	i = out->nmb_paths - 1;
	flg = 0;
	while (i >= 0)
	{
		j = out->arr_paths[i].path_leng - 1;
		while (j >= 0)
		{
			if (out->arr_paths[i].path[j].ant_index != 0)
			{
				ft_printf("L%d-%s ", out->arr_paths[i].path[j].ant_index,
						out->arr_paths[i].path[j].name);
				flg = 1;
			}
			j--;
		}
		i--;
	}
	if (flg == 1)
		ft_printf("!\n");
	return (flg);
}

void	output_ants(t_input_data *data, t_output_data *out)
{
	int flg;
	int ant_ind;

	flg = 1;
	ant_ind = 1;
	while (flg == 1)
	{
		move_ants(out);
		push_ants(data, out, &ant_ind);
		flg = print_ants(out);
	}
}

void	del_arr_path(t_output_data *out)
{
	int i;

	i = 0;
	while (i < out->nmb_paths)
	{
		free(out->arr_paths[i].path);
		i++;
	}
	free(out->arr_paths);
}

void	inner_whl_f_run_ants(t_vld_path_elem *crnt_el,
		t_output_data *out, t_lst_vld_path *crnt, int *j)
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
void cnt_ants_for_each_path(t_lst_vld_path *lst_vld_path, int data_ants, int x, int cnt_paths)
{
	int cnt;
	int sum_ants;
	t_lst_vld_path *crnt_path;

	cnt = 0;
	sum_ants = 0;
	crnt_path = lst_vld_path;
	while(cnt < cnt_paths)
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

int distribute_ants_to_paths(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
	int x;
	int sum_d;
	int cnt_paths;
	t_lst_vld_path *crnt_val_path;

	x = 0;
	cnt_paths = 1;
	crnt_val_path = lst_vld_path;
	sum_d = lst_vld_path->leng;
	while (crnt_val_path)
	{
		x = (sum_d + data->cnt_ants) / cnt_paths;
		if (crnt_val_path->next == NULL || crnt_val_path->next->leng > x)
			break;
		cnt_paths++;
		crnt_val_path = crnt_val_path->next;
		sum_d = sum_d + crnt_val_path->leng;
	}
	cnt_ants_for_each_path(lst_vld_path, data->cnt_ants, x, cnt_paths);
	return (cnt_paths);
}

void print_ants_in_one_line(int cnt_ants, char *end_room_name)
{
	int i;

	i = 1;
	while(cnt_ants >= i)
	{
		ft_printf("L%d-%s ", i, end_room_name);
		i++;
	}
	exit(0);
}

void	run_ants(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
	int				i;
	int				j;
	t_output_data	out;
	t_lst_vld_path	*crnt;
	t_vld_path_elem	*crnt_el;

	i = 0;
	crnt = lst_vld_path;
	out.nmb_paths = distribute_ants_to_paths(data, lst_vld_path);
	out.arr_paths = (t_out_path*)malloc(sizeof(t_out_path) * out.nmb_paths);
	while (crnt && out.nmb_paths > i)
	{
		crnt_el = crnt->frst_path_el;
		out.arr_paths[i].path =
			(t_out_room*)malloc(sizeof(t_out_room) * crnt->leng);
		j = 0;
		if (crnt->leng > 1)
		{
			crnt_el->i = i;
			inner_whl_f_run_ants(crnt_el, &out, crnt, &j);
		}
		else
			print_ants_in_one_line(data->cnt_ants, data->end_room_name);
		out.arr_paths[i].nmb_ants = crnt->x;
		out.arr_paths[i].path_leng = crnt->leng;
		out.arr_paths[i].path[j].name = data->end_room_name;
		out.arr_paths[i].path[j].ant_index = 0;
		i++;
		crnt = crnt->next;
	}
	output_ants(data, &out);
	del_arr_path(&out);
}


