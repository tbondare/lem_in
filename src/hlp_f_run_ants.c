/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hlp_f_run_ants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:27:05 by tbondare          #+#    #+#             */
/*   Updated: 2019/09/15 19:34:15 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"

void	print_ants_in_one_line(int cnt_ants, char *end_room_name)
{
	int i;

	i = 1;
	while (cnt_ants >= i)
	{
		ft_printf("L%d-%s ", i, end_room_name);
		i++;
	}
	exit(0);
}

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
		ft_printf("\n");
	return (flg);
}

void	output_ants(t_input_data *data, t_output_data *out)
{
	int flg;
	int ant_ind;
	int cnt;

	flg = 1;
	ant_ind = 1;
	cnt = 0;
	while (flg == 1)
	{
		cnt++;
		move_ants(out);
		push_ants(data, out, &ant_ind);
		flg = print_ants(out);
		ft_printf("%d\n", cnt);
	}
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
