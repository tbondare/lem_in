/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hlp_f_run_ants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:27:05 by tbondare          #+#    #+#             */
/*   Updated: 2019/09/03 15:04:29 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftlemin.h"

int		ft_round(float x)
{
	int x_int;
	int c;

	x_int = x;
	x = x - x_int;
	while (x)
	{
		c = x * 10;
		if (c >= 5)
			return (++x_int);
		if (c < 4)
			return (x_int);
		x = x - c;
	}
	return (x_int);
}

void	round_ants(t_input_data *data, t_lst_vld_path **crnt, int sum_y)
{
	while (*crnt)
	{
		(*crnt)->x = ft_round((float)data->cnt_ants * (*crnt)->y / sum_y);
		*crnt = (*crnt)->next;
	}
}

int		cnt_x_for_every_valpath(t_input_data *data,
		t_lst_vld_path *lst_vld_path)
{
	int				prdct_b;
	int				sum_y;
	int				nmbr_path;
	t_lst_vld_path	*crnt;

	sum_y = 0;
	prdct_b = 1;
	crnt = lst_vld_path;
	nmbr_path = 0;
	while (crnt)
	{
		nmbr_path++;
		prdct_b = prdct_b * crnt->leng;
		crnt = crnt->next;
	}
	crnt = lst_vld_path;
	while (crnt)
	{
		crnt->y = prdct_b / crnt->leng;
		sum_y = sum_y + crnt->y;
		crnt = crnt->next;
	}
	crnt = lst_vld_path;
    round_ants(data, &crnt, sum_y);
	return (nmbr_path);
}

void	move_ants(t_output_data *out)
{
	int i;
	int j;

	i = 0;
	while (i < out->nmb_paths)
	{
		j = out->arr_paths[i].path_leng - 1;
		while (j > 0)
		{
			out->arr_paths[i].path[j].ant_index =
				out->arr_paths[i].path[j - 1].ant_index;
			j--;
		}
		i++;
	}
}

void	push_ants(t_input_data *data, t_output_data *out, int *ant_ind)
{
	int i;

	i = out->nmb_paths - 1;
	while (i >= 0)
	{
		if (out->arr_paths[i].nmb_ants == 0)
		{
			out->arr_paths[i].path[0].ant_index = 0;
			i--;
			continue;
		}
		if (*ant_ind <= data->cnt_ants)
			out->arr_paths[i].path[0].ant_index = (*ant_ind)++;
		else
			out->arr_paths[i].path[0].ant_index = 0;
		out->arr_paths[i].nmb_ants--;
		i--;
	}
}
