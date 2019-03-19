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

void find_next_link(t_input_data data, t_list_queue *frst_queue_el,
        t_list_tubes **crn_tube)
{
    while (*crn_tube)
    {
        if ((*crn_tube)->first == frst_queue_el->crn_room_name ||
                (*crn_tube)->second == frst_queue_el->crn_room_name)
            break ;
        *crn_tube = (*crn_tube)->next_tb;
    }
}

int check_room_is_end(char *end_room, t_list_tubes *crn_tube)
{
    if (ft_strcmp(end_room, crn_tube->first) != 0)
        if (ft_strcmp(end_room, crn_tube->second) != 0)
            return (0);
    return (1);
}

t_lst_vld_path *find_valid_path(t_input_data data)
{
    t_queue_data queue;
    t_list_tubes *crn_tube;
    char *end_room;

    queue.frst_queue_el = (t_list_queue*)malloc(sizeof(t_list_queue));
    queue.frst_queue_el->crn_room_name = find_start_room(data);
    end_room = find_end_room(data);
    while (queue.frst_queue_el)
    {
        crn_tube = data.frst_tb;
        while (crn_tube)
        {
            find_next_link(data, queue.frst_queue_el, &crn_tube);
            if (check_room_is_end(end_room, crn_tube) == 1)

        }
        queue.mem_queue = queue.frst_queue_el;
        queue.frst_queue_el = queue.frst_queue_el->next;
        free(queue.mem_queue);
    }
}