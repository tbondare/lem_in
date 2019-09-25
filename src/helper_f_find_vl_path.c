/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_f_find_vl_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 16:39:19 by tbondare          #+#    #+#             */
/*   Updated: 2019/09/15 19:29:12 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"

t_list_rooms	*find_start_room(t_input_data *data)
{
	t_list_rooms *crn_room;

	crn_room = data->frst_rm;
	while (crn_room->is_sart != 1 && crn_room->next_rm)
		crn_room = crn_room->next_rm;
	if (crn_room->is_sart != 1 && crn_room->next_rm == NULL)
	{
		ft_printf("Input data isn't correct: there isn't start room");
		exit(1);
	}
	return (crn_room);
}

void			add_queue_el(t_queue_data *que, t_path *el_que)
{
	t_list_queue *crn_qel;

	crn_qel = que->last_q_el;
	que->last_q_el = (t_list_queue*)malloc(sizeof(t_list_queue));
	que->last_q_el->path = el_que;
	que->last_q_el->next = NULL;
	if (que->frst_queue_el != NULL)
		crn_qel->next = que->last_q_el;
	else
		que->frst_queue_el = que->last_q_el;
}

void			del_first_queue_el(t_queue_data *queue)
{
	queue->mem_queue = queue->frst_queue_el;
	queue->frst_queue_el = queue->frst_queue_el->next;
	free(queue->mem_queue);
}

void			del_queue(t_queue_data *queue)
{
	t_list_queue *mem_q;

	while (queue->frst_queue_el)
	{
		mem_q = queue->frst_queue_el->next;
		free(queue->frst_queue_el);
		queue->frst_queue_el = mem_q;
	}
}
