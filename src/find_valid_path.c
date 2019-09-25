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

    mem_path = path;
    path = (t_path*)malloc(sizeof(t_path));
    path->prev = mem_path;
    path->vertex = room;
    return(path);
}

void loop_for_links_crn_room(t_queue_data *queue)
{
	t_links			*crn_rm_ln;
	t_path *crn_q_el;
	int a;

	crn_rm_ln = queue->frst_queue_el->path->vertex->link;
	while(crn_rm_ln)
	{
		a = 0;
		crn_q_el = queue->frst_queue_el->path;
		while(crn_q_el)
		{
			if(ft_strequ(crn_rm_ln->linked_room->name, crn_q_el->vertex->name) == 1)
				a++;
            crn_q_el = crn_q_el->prev;
		}
        if(a == 0 && crn_rm_ln->linked_room->is_in_val_pth == 0)
			add_queue_el(queue, add_room_to_path(queue->frst_queue_el->path,
			        crn_rm_ln->linked_room));
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
		if (queue.frst_queue_el->path->vertex->is_in_val_pth == 1)
        {
            del_first_queue_el(&queue);
            continue ;
        }
		if (queue.frst_queue_el->path->vertex->is_end == 1)
			save_val_path(&frst_vl_pth, queue.frst_queue_el->path, data);
		else
			loop_for_links_crn_room(&queue);
		del_first_queue_el(&queue);
	}
	return (frst_vl_pth);
}