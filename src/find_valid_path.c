/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_valid_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:46:09 by tbondare          #+#    #+#             */
/*   Updated: 2019/09/27 18:15:05 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"

void			loop_for_links_crn_room(t_input_data *data, t_queue_data *queue)
{
	t_links			*crn_rm_ln;
	t_path			*crn_q_el;

	crn_rm_ln = queue->frst_queue_el->path->vertex->link;
	while (crn_rm_ln)
	{
		if (crn_rm_ln->linked_room->is_in_val_pth != 0
			|| crn_rm_ln->linked_room->cnt_was_in_room > 30)
		{
			crn_rm_ln = crn_rm_ln->next;
			continue ;
		}
		data->a = 0;
		crn_q_el = queue->frst_queue_el->path;
		while (crn_q_el)
		{
			if (crn_rm_ln->linked_room == crn_q_el->vertex)
				data->a++;
			crn_q_el = crn_q_el->prev;
		}
		if (data->a == 0)
			add_queue_el(queue, add_room_to_path(data,
						queue->frst_queue_el->path, crn_rm_ln->linked_room));
		crn_rm_ln = crn_rm_ln->next;
	}
}

void			save_val_path(t_lst_vld_path **frst_vl_pth, t_path *crn,
		t_input_data *data)
{
	t_lst_vld_path	*mem_vld_path;
	t_vld_path_elem	*mem_path_el;

	mem_vld_path = add_val_path(frst_vl_pth);
	data->flg_ants++;
	data->end_room_name = crn->vertex->name;
	crn = crn->prev;
	while (!crn->vertex->is_sart)
	{
		mem_path_el = mem_vld_path->frst_path_el;
		mem_vld_path->frst_path_el =
			(t_vld_path_elem*)malloc(sizeof(t_vld_path_elem));
		mem_vld_path->frst_path_el->next = mem_path_el;
		mem_vld_path->frst_path_el->room = crn->vertex;
		crn->vertex->is_in_val_pth = 1;
		mem_vld_path->leng++;
		crn = crn->prev;
	}
}

int				check_room_is_val_path(t_queue_data *queue)
{
	t_path *path;

	path = queue->frst_queue_el->path;
	while (!path->vertex->is_sart)
	{
		if (path->vertex->is_in_val_pth == 1)
			return (1);
		path = path->prev;
	}
	return (0);
}

void init_data_and_queue(t_input_data *data, t_queue_data *queue)
{
	data->a = 0;
	data->flg_ants = 0;
	data->del_path = NULL;
	queue->last_q_el = NULL;
	queue->frst_queue_el = NULL;
}

t_lst_vld_path	*find_valid_path(t_input_data *data)
{
	t_queue_data	queue;
	t_lst_vld_path	*frst_vl_pth;

	init_data_and_queue(data, &queue);
	frst_vl_pth = NULL;
	add_queue_el(&queue, create_path_for_queue(data));
	while (queue.frst_queue_el)
	{
		if (data->flg_ants == data->cnt_ants)
		{
			del_queue(&queue);
			return (frst_vl_pth);
		}
		if (check_room_is_val_path(&queue) == 1)
		{
			del_first_queue_el(&queue);
			continue ;
		}
		if (queue.frst_queue_el->path->vertex->is_end == 1)
			save_val_path(&frst_vl_pth, queue.frst_queue_el->path, data);
		else
			loop_for_links_crn_room(data, &queue);
		del_first_queue_el(&queue);
	}
	return (frst_vl_pth);
}
