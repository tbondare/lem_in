#include "libftlemin.h"
#include "stdio.h"

t_list_rooms *find_start_room(t_input_data *data)
{
    t_list_rooms *crn_room;

    crn_room = data->frst_rm;
    while (crn_room->is_sart != 1 && crn_room->next_rm)
        crn_room = crn_room->next_rm;
    if (crn_room->is_sart != 1 && crn_room->next_rm == NULL)
    {
        //TODO:error;
        return (0);
    }
    return (crn_room);
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

void add_come_from_room(t_list_rooms *come_from_rm, t_list_rooms *crnt_rm)
{
    t_ls_come_from *cm_fr_el;
    t_ls_come_from *list_iter;

    list_iter = crnt_rm->from;
    while (list_iter != NULL && list_iter->next)
        list_iter = list_iter->next;
    cm_fr_el = (t_ls_come_from*)malloc(sizeof(t_ls_come_from));
    cm_fr_el->room = come_from_rm;
    if (list_iter != NULL)
        list_iter->next = cm_fr_el;
    else
        crnt_rm->from = cm_fr_el;
    cm_fr_el->next = NULL;
}

void save_val_path(t_lst_vld_path **frst_vl_pth, t_list_rooms *crn_room)
{
    t_lst_vld_path *mem_vld_path;
    t_vld_path_elem *mem_path_el;
    t_ls_come_from *mem_from = NULL;

    mem_vld_path = *frst_vl_pth;
    *frst_vl_pth = (t_lst_vld_path*)malloc(sizeof(t_lst_vld_path));
    (*frst_vl_pth)->y = 0;
    (*frst_vl_pth)->x = 0;
    (*frst_vl_pth)->next = mem_vld_path;
    (*frst_vl_pth)->frst_path_el = NULL;
    (*frst_vl_pth)->leng = 1;
    while (!crn_room->is_sart)
    {
        mem_path_el = (*frst_vl_pth)->frst_path_el;
        (*frst_vl_pth)->frst_path_el = (t_vld_path_elem*)malloc(sizeof(t_vld_path_elem));
        (*frst_vl_pth)->frst_path_el->next = mem_path_el;
        (*frst_vl_pth)->frst_path_el->room = crn_room;
        printf("!!!!!sv_val_path %s\n", crn_room->name);
        crn_room->is_in_val_pth = 1;
        while (crn_room->from->room->is_in_val_pth == 1)
        {
            mem_from = crn_room->from;
            crn_room->from = crn_room->from->next;
            free (mem_from);
        }
        (*frst_vl_pth)->leng++;
        crn_room = crn_room->from->room;
    }
    printf("leng %d", (*frst_vl_pth)->leng);
}

t_lst_vld_path *find_valid_path(t_input_data *data)
{
    t_queue_data queue;
    t_links *crn_rm_ln;
    t_lst_vld_path *frst_vl_pth;

    queue.last_q_el = NULL;
    queue.frst_queue_el = NULL;
    frst_vl_pth = NULL;
    add_queue_el(&queue, find_start_room(data));
    while (queue.frst_queue_el)
    {
        printf("crn_rm %s\n", queue.frst_queue_el->crn_room->name);
        queue.frst_queue_el->crn_room->was_in_room = 1;
        crn_rm_ln = queue.frst_queue_el->crn_room->link;
        while (crn_rm_ln)
        {
            printf("   lnk_rm %s\n", crn_rm_ln->linked_room->name);
            if (crn_rm_ln->linked_room->is_end == 1)
            {
                save_val_path(&frst_vl_pth, queue.frst_queue_el->crn_room);
                data->end_room_name = crn_rm_ln->linked_room->name;
                printf("   save_val_path\n");
            }
            else if (crn_rm_ln->linked_room->was_in_room == 1)
            {
                crn_rm_ln = crn_rm_ln->next;
                printf("   was_in_room\n");
                continue;
            }
            else if(crn_rm_ln->linked_room->is_in_queue == 1)
            {
                add_come_from_room(queue.frst_queue_el->crn_room, crn_rm_ln->linked_room);
                printf("      come_from %s\n", crn_rm_ln->linked_room->from->room->name);
                crn_rm_ln = crn_rm_ln->next;
                printf("   is_in_queue\n");
                continue;
            }
            else
            {
                crn_rm_ln->linked_room->is_in_queue = 1;
                add_come_from_room(queue.frst_queue_el->crn_room, crn_rm_ln->linked_room);
                printf("      come_from %s\n", crn_rm_ln->linked_room->from->room->name);
                add_queue_el(&queue, crn_rm_ln->linked_room);
                printf("   add_queue_el\n");
            }
            crn_rm_ln = crn_rm_ln->next;
        }
        del_first_queue_el(&queue);
    }
    return (frst_vl_pth);
}