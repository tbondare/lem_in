/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_valid_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:46:09 by tbondare          #+#    #+#             */
/*   Updated: 2019/08/28 19:40:27 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftlemin.h"

void			whl_f_save_vl_path(t_list_rooms *crn_room)
{
	t_ls_come_from *mem_from;

	mem_from = NULL;
	while (crn_room->from->room->is_in_val_pth == 1)
	{
		mem_from = crn_room->from;
		crn_room->from = crn_room->from->next;
		free(mem_from);
	}
}

void			save_val_path(t_lst_vld_path **frst_vl_pth,
		t_list_rooms *crn_room, t_input_data *data)
{
	t_lst_vld_path	*mem_vld_path;
	t_vld_path_elem	*mem_path_el;

	mem_vld_path = *frst_vl_pth;
	*frst_vl_pth = (t_lst_vld_path*)malloc(sizeof(t_lst_vld_path));
	(*frst_vl_pth)->y = 0;
	(*frst_vl_pth)->x = 0;
	(*frst_vl_pth)->next = mem_vld_path;
	(*frst_vl_pth)->frst_path_el = NULL;
	(*frst_vl_pth)->leng = 1;
	data->flg_ants++;
	while (!crn_room->is_sart)
	{
		mem_path_el = (*frst_vl_pth)->frst_path_el;
		(*frst_vl_pth)->frst_path_el =
			(t_vld_path_elem*)malloc(sizeof(t_vld_path_elem));
		(*frst_vl_pth)->frst_path_el->next = mem_path_el;
		(*frst_vl_pth)->frst_path_el->room = crn_room;
		crn_room->is_in_val_pth = 1;
		whl_f_save_vl_path(crn_room);
		(*frst_vl_pth)->leng++;
		crn_room = crn_room->from->room;
	}
}

void			els_f_whl_fnd_vl_path(t_links *crn_rm_ln,
		t_queue_data **queue)
{
	crn_rm_ln->linked_room->is_in_queue = 1;
	add_come_from_room((*queue)->frst_queue_el->crn_room,
			crn_rm_ln->linked_room);
	add_queue_el(*queue, crn_rm_ln->linked_room);
}

void			whl_f_find_val_path(t_input_data *data, t_links *crn_rm_ln,
		t_queue_data *queue, t_lst_vld_path **frst_vl_pth)
{
	while (crn_rm_ln)
	{
		if (crn_rm_ln->linked_room->is_end == 1)
		{
			save_val_path(frst_vl_pth, queue->frst_queue_el->crn_room, data);
			data->end_room_name = crn_rm_ln->linked_room->name;
		}
		else if (crn_rm_ln->linked_room->was_in_room == 1)
		{
			crn_rm_ln = crn_rm_ln->next;
			continue;
		}
		else if (crn_rm_ln->linked_room->is_in_queue == 1)
		{
			add_come_from_room(queue->frst_queue_el->crn_room,
					crn_rm_ln->linked_room);
			crn_rm_ln = crn_rm_ln->next;
			continue;
		}
		else
			els_f_whl_fnd_vl_path(crn_rm_ln, &queue);
		crn_rm_ln = crn_rm_ln->next;
	}
}

t_lst_vld_path	*find_valid_path(t_input_data *data)
{
	t_queue_data	queue;
	t_links			*crn_rm_ln;
	t_lst_vld_path	*frst_vl_pth;

	data->flg_ants = 0;
	crn_rm_ln = NULL;
	queue.last_q_el = NULL;
	queue.frst_queue_el = NULL;
	frst_vl_pth = NULL;
	add_queue_el(&queue, find_start_room(data));
	while (queue.frst_queue_el)
	{
		if (data->flg_ants == data->cnt_ants)
		{
			del_queue(&queue);
			return (frst_vl_pth);
		}
		queue.frst_queue_el->crn_room->was_in_room = 1;
		crn_rm_ln = queue.frst_queue_el->crn_room->link;
		whl_f_find_val_path(data, crn_rm_ln, &queue, &frst_vl_pth);
		del_first_queue_el(&queue);
	}
	return (frst_vl_pth);
}
