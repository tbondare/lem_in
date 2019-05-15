//
// Created by tanya on 19.09.18.
//

#include "libftlemin.h"

char *find_start_room(t_input_data data)
{
    t_list_rooms *crn_room;

    crn_room = data.frst_rm;
    while (crn_room->is_sart != 1 && crn_room->next_rm)
        crn_room = crn_room->next_rm;
    if (crn_room->is_sart != 1 && crn_room->next_rm == NULL)
    {
        //TODO:error;
        return (0);
    }
    return (crn_room->name);
}

char *find_end_room(t_input_data data)
{
    t_list_rooms *crn_room;
    crn_room = data.frst_rm;
    while (crn_room->is_end != 1 && crn_room->next_rm)
        crn_room = crn_room->next_rm;
    if (crn_room->is_end != 1 && crn_room->next_rm == NULL)
    {
        //TODO:error;
        return (0);
    }
    return (crn_room->name);
}

int check_room_is_end(char *end_room, t_list_tubes *crn_tube)
{
    if (ft_strcmp(end_room, crn_tube->first) != 0)
        if (ft_strcmp(end_room, crn_tube->second) != 0)
            return (0);
    return (1);
}

void add_queue_el(t_queue_data *que, t_list_rooms *el_que)
{
    t_list_queue *crn_qel;

    crn_qel = que->last_q_el;
    que->last_q_el = (t_list_queue*)malloc(sizeof(t_list_queue));
    que->last_q_el->crn_room = el_que;
    que->last_q_el->next = NULL;
    if(que->frst_queue_el != NULL)
        crn_qel->next = que->last_q_el;
    else
        que->frst_queue_el = que->last_q_el ;
}

void del_first_queue_el(t_queue_data *queue)
{
    queue->mem_queue = queue->frst_queue_el;
    queue->frst_queue_el = queue->frst_queue_el->next;
    free(queue->mem_queue);
}

void save_val_path(t_lst_vld_path **frst_vl_pth, t_list_rooms *crn_room)
{

}

t_lst_vld_path *find_valid_path(t_input_data data)
{
    t_queue_data queue;
    t_links *crn_rm_ln;
    char *end_room;
    t_lst_vld_path *frst_vl_pth;

    queue.last_q_el = NULL;
    queue.frst_queue_el = NULL;
    add_queue_el(&queue, find_start_room(data));
    end_room = find_end_room(data);
    while (queue.frst_queue_el)
    {
        queue.frst_queue_el->crn_room->was_in_room = 1;
        crn_rm_ln = queue.frst_queue_el->crn_room->link;
        while (crn_rm_ln)
        {
            if (check_room_is_end(end_room, crn_rm_ln->linked_room->name) == 1)
            {
                save_val_path(&frst_vl_pth, queue.frst_queue_el->crn_room);
            }
            else if (crn_rm_ln->linked_room->was_in_room == 1)
            {
                crn_rm_ln = crn_rm_ln->next;
                continue;
            }
            else
            {
                crn_rm_ln->next_rm->was_in_room = 1;

            }
            crn_rm_ln = crn_rm_ln->next;
        }
        del_first_queue_el(&queue);
    }
}