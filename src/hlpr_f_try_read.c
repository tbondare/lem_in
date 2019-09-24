/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hlpr_f_try_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:01:21 by tbondare          #+#    #+#             */
/*   Updated: 2019/08/31 17:24:22 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"

void	init_room(char *line, t_input_data *data)
{
	int i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	data->frst_rm->name = ft_strsub(line, 0, i);
	data->frst_rm->x = ft_atoi(&line[++i]);
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	data->frst_rm->y = ft_atoi(&line[++i]);
}

void	add_new_rm(t_input_data *data, t_list_rooms **new)
{
	(*new)->name = NULL;
	(*new)->x = 0;
	(*new)->y = 0;
	(*new)->is_sart = 0;
	(*new)->is_end = 0;
	(*new)->is_in_val_pth = 0;
	(*new)->link = NULL;
	(*new)->from = NULL;
	(*new)->next_rm = data->frst_rm;
	data->frst_rm = *new;
}

void	add_rm_to_list(t_input_data *data)
{
	t_list_rooms *new;

	if (data->frst_rm == NULL)
	{
		data->frst_rm = (t_list_rooms*)malloc(sizeof(t_list_rooms));
		data->frst_rm->name = NULL;
		data->frst_rm->x = 0;
		data->frst_rm->y = 0;
		data->frst_rm->is_sart = 0;
		data->frst_rm->is_end = 0;
		data->frst_rm->is_in_val_pth = 0;
		data->frst_rm->link = NULL;
		data->frst_rm->from = NULL;
		data->frst_rm->next_rm = NULL;
	}
	else
	{
		new = (t_list_rooms*)malloc(sizeof(t_list_rooms));
		add_new_rm(data, &new);
	}
}

int		is_room_exist(t_input_data *data, char *name_rm)
{
	int				cnt;
	t_list_rooms	*cur_rm;

	cnt = 0;
	cur_rm = data->frst_rm;
	while (cur_rm != NULL)
	{
		if (ft_strequ(name_rm, cur_rm->name) == 1)
			cnt++;
		cur_rm = cur_rm->next_rm;
	}
	if (cnt == 0)
		return (0);
	return (1);
}

void	add_tb_to_list(t_input_data *data)
{
	t_list_tubes *new;

	if (data->frst_tb == NULL)
	{
		data->frst_tb = (t_list_tubes*)malloc(sizeof(t_list_tubes));
		data->frst_tb->first = NULL;
		data->frst_tb->second = NULL;
		data->frst_tb->next_tb = NULL;
	}
	else
	{
		new = (t_list_tubes*)malloc(sizeof(t_list_tubes));
		new->first = NULL;
		new->second = NULL;
		new->next_tb = data->frst_tb;
		data->frst_tb = new;
	}
}
