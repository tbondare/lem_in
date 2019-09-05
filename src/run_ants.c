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

#include "libftlemin.h"

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
	ft_printf("\n");
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
		out->arr_paths[i].nmb_ants = crnt->x;
		out->arr_paths[i].path_leng = crnt->leng;
		crnt_el = crnt_el->next;
		(*j)++;
	}
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
	out.nmb_paths = cnt_x_for_every_valpath(data, lst_vld_path);
	out.arr_paths = (t_out_path*)malloc(sizeof(t_out_path) * out.nmb_paths);
	while (crnt)
	{
		crnt_el = crnt->frst_path_el;
		out.arr_paths[i].path =
			(t_out_room*)malloc(sizeof(t_out_room) * crnt->leng);
		crnt_el->i = i;
		j = 0;
		inner_whl_f_run_ants(crnt_el, &out, crnt, &j);
		out.arr_paths[i].path[j].name = data->end_room_name;
		out.arr_paths[i].path[j].ant_index = 0;
		i++;
		crnt = crnt->next;
	}
	output_ants(data, &out);
	del_arr_path(&out);
}
