//
// Created by tanya on 19.09.18.
//

#include "libftlemin.h"

char *find_start_room(t_input_data data)
{
    t_list_rooms *crn_room;

    crn_room = data.frst_rm;
    while (crn_room->room.is_sart != 1 && crn_room->next_rm)
        crn_room = crn_room->next_rm;
    if (crn_room->room.is_sart != 1 && crn_room->next_rm == NULL)
    {
        //TODO:error;
        return (0);
    }
    return (crn_room->room.name);
}

char *find_end_room(t_input_data data)
{
    t_list_rooms *crn_room;
    crn_room = data.frst_rm;
    while (crn_room->room.is_end != 1 && crn_room->next_rm)
        crn_room = crn_room->next_rm;
    if (crn_room->room.is_end != 1 && crn_room->next_rm == NULL)
    {
        //TODO:error;
        return (0);
    }
    return (crn_room->room.name);
}

void find_next_link(t_input_data data, t_list_queue *frst_queue_el,
        t_list_tubes **crn_tube)
{
    while (*crn_tube)
    {
        if ((*crn_tube)->tube.first == frst_queue_el->crn_room_name ||
                (*crn_tube)->tube.second == frst_queue_el->crn_room_name)
            break ;
        *crn_tube = (*crn_tube)->next_tb;
    }
}

int check_room_is_end(char *end_room, t_list_tubes *crn_tube)
{
    if (ft_strcmp(end_room, crn_tube->tube.first) != 0)
        if (ft_strcmp(end_room, crn_tube->tube.second) != 0)
            return (0);
    return (1);
}

t_lst_vld_path *find_valid_path(t_input_data data)
{
    t_list_queue *frst_queue_el;
    t_list_queue *mem_queue;
    t_list_queue *last_q_el;
    t_list_tubes *crn_tube;
    char *end_room;

    frst_queue_el = (t_list_queue*)malloc(sizeof(t_list_queue));
    frst_queue_el->crn_room_name = find_start_room(data);
    end_room = find_end_room(data);
    while (frst_queue_el)
    {
        crn_tube = data.frst_tb;
        while (crn_tube)
        {
            find_next_link(data, frst_queue_el, &crn_tube);
            check_room_is_end(end_room, crn_tube);
        }
        mem_queue = frst_queue_el;
        frst_queue_el = frst_queue_el->next;
        free(mem_queue);
    }
}