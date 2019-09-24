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

#include "./inc/libftlemin.h"

//void			whl_f_save_vl_path(t_list_rooms *crn_room)
//{
//	t_ls_come_from *mem_from;
//
//	mem_from = NULL;
//	while (crn_room->from && crn_room->from->room->is_in_val_pth == 1)
//	{
//		mem_from = crn_room->from;
//		crn_room->from = crn_room->from->next;
//		free(mem_from);
//	}
//}

t_lst_vld_path *add_val_path(t_lst_vld_path	**frst_vl_pth)
{
	t_lst_vld_path *mem_vld_path;
	t_lst_vld_path *new_vld_path;

	if (*frst_vl_pth == NULL)
	{
		new_vld_path = (t_lst_vld_path*)malloc(sizeof(t_lst_vld_path));
		*frst_vl_pth = new_vld_path;
	}
	else
	{
		mem_vld_path = *frst_vl_pth;
		while(mem_vld_path->next)
			mem_vld_path = mem_vld_path->next;
		mem_vld_path->next = (t_lst_vld_path*)malloc(sizeof(t_lst_vld_path));
		new_vld_path = mem_vld_path->next;
	}

	new_vld_path->y = 0;
	new_vld_path->x = 0;
	new_vld_path->next = NULL;
	new_vld_path->frst_path_el = NULL;
	new_vld_path->leng = 1;
	return (new_vld_path);
}

void			save_val_path(t_lst_vld_path **frst_vl_pth,
		t_list_rooms *crn_room, t_input_data *data)
{
	t_lst_vld_path	*mem_vld_path;
	t_vld_path_elem	*mem_path_el;

	mem_vld_path = add_val_path(frst_vl_pth);
	data->flg_ants++;
	while (!crn_room->is_sart)
	{
		mem_path_el = mem_vld_path->frst_path_el;
		mem_vld_path->frst_path_el =
			(t_vld_path_elem*)malloc(sizeof(t_vld_path_elem));
		mem_vld_path->frst_path_el->next = mem_path_el;
		mem_vld_path->frst_path_el->room = crn_room;
		crn_room->is_in_val_pth = 1;
//		whl_f_save_vl_path(crn_room);
		mem_vld_path->leng++;
		crn_room = crn_room->from->room;
	}
}

void			els_f_whl_fnd_vl_path(t_links *crn_rm_ln,
		t_queue_data **queue)
{
	crn_rm_ln->linked_room->is_in_queue = 1;
	add_come_from_room((*queue)->frst_queue_el->crn_room,
			crn_rm_ln->linked_room);
	if (crn_rm_ln->linked_room->depth == -1)
		crn_rm_ln->linked_room->depth = (*queue)->frst_queue_el->crn_room->depth + 1;
	add_queue_el(*queue, crn_rm_ln->linked_room);
}

int check_is_val_path(t_list_rooms *crn_room, int level, int max_level)
{
	t_ls_come_from *mem_from;
    int res;

    if(crn_room->is_in_val_pth == 1)
		return (0);
	if (crn_room->is_sart == 1)
		return (1);
	if(level >= max_level)
		return (0);
    res = 0;
    while(crn_room->from)
	{
		if(check_is_val_path(crn_room->from->room, level + 1, max_level) == 1)
		{
			res = 1;
			break ;
		}
		else
		{
			if (crn_room->from == NULL)
				return (0);
			mem_from = crn_room->from;
			crn_room->from = crn_room->from->next;
			free(mem_from);
		}
	}
//	if(res == 0)
//	{
//		crn_room->was_in_room = 0;
//		crn_room->is_in_queue = 0;
//	}
	return (res);
}

int null_flags_frome(t_list_rooms *crn_room)
{
	t_ls_come_from *crnt_frome;

	crnt_frome = crn_room->from;
	while (!crn_room->is_sart)
	{
		if(crn_room->is_in_val_pth == 1)
			return(0);
		crnt_frome = crn_room->from;
		while (crnt_frome)
		{
			if (crnt_frome->room->is_in_val_pth == 1)
				crnt_frome = crnt_frome->next;
			else
				break ;
		}
		if (crnt_frome == NULL)
			return (0);
		crn_room = crnt_frome->room;
	}
	return (0);
}

void			whl_f_find_val_path(t_input_data *data, t_links *crn_rm_ln,
		t_queue_data *queue, t_lst_vld_path **frst_vl_pth)
{
	while (crn_rm_ln)
	{
		if (crn_rm_ln->linked_room->is_end == 1)
		{
			if (check_is_val_path(queue->frst_queue_el->crn_room, 0, queue->frst_queue_el->crn_room->depth) == 0)
			{
//				null_flags_frome(queue->frst_queue_el->crn_room);
				crn_rm_ln = crn_rm_ln->next;
				continue ;
			}
			save_val_path(frst_vl_pth, queue->frst_queue_el->crn_room, data);
			data->end_room_name = crn_rm_ln->linked_room->name;
			break ;
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

t_path *create_path_for_queue(t_input_data *data)
{
	t_path *path;

	path = (t_path*)malloc(sizeof(t_path));
	path->vertex = find_start_room(data);
	path->prev = NULL;
	return(path);
}

t_path *add_room_to_path(t_path *path, t_list_rooms *room)
{
	t_path *mem_path;
	

	path = (t_path*)malloc(sizeof(t_path));
	path->vertex = find_start_room(data);
	path->prev = NULL;
	return(path);
}

void loop_for_links_crn_room(t_queue_data *queue)
{
	t_links			*crn_rm_ln;
	t_path *crn_path;
	int a;

	crn_rm_ln = queue->frst_queue_el->path->vertex->link;
	while(crn_rm_ln)
	{
		a = 0;
		crn_path = queue->frst_queue_el->path;
		while(crn_path)
		{
			if(ft_strequ(crn_rm_ln->linked_room->name,
						 crn_path->vertex->name) == 1)
				a++;
			crn_path = crn_path->prev;
		}
		if (a == 0)
			add_queue_el(queue, add_room_to_path
					(queue->frst_queue_el->path, crn_rm_ln->linked_room));
		crn_rm_ln = crn_rm_ln->next;
	}
}

t_lst_vld_path	*find_valid_path(t_input_data *data)
{
	t_queue_data	queue;
	t_lst_vld_path	*frst_vl_pth;

	data->flg_ants = 0;
	queue.last_q_el = NULL;
	queue.frst_queue_el = NULL;
	frst_vl_pth = NULL;
	add_queue_el(&queue, create_path_for_queue(data));
	while (queue.frst_queue_el)
	{
		if (data->flg_ants == data->cnt_ants)
		{
			del_queue(&queue);
			return (frst_vl_pth);
		}
		if (queue.frst_queue_el->path->vertex->is_end == 1)
			save_val_path(frst_vl_pth, queue.frst_queue_el->path);
		else
			loop_for_links_crn_room(&queue);
		del_first_queue_el(&queue);
	}
	return (frst_vl_pth);
}
