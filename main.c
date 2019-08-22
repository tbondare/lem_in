#include "libftlemin.h"
#include "stdio.h"

t_list_rooms *found_ptr_room_by_name(t_input_data *data, char *name)
{
    t_list_rooms *crnt_rm;

    crnt_rm = data->frst_rm;
    while(crnt_rm)
    {
        if (ft_strequ (crnt_rm->name, name) == 1)
            return (crnt_rm);
        crnt_rm = crnt_rm->next_rm;
    }
    return (0);
}

int is_same_link(t_links *lnk, char *name)
{
    t_links *crn_lnk;

    crn_lnk = lnk;
    while (crn_lnk)
    {
        if (ft_strequ(crn_lnk->linked_room->name, name) == 1)
            return (1);
        crn_lnk = crn_lnk->next;
    }
    return(0);
}

void add_tubes_to_rooms(t_input_data *data)
{
    t_list_rooms *crnt_rm;
    t_list_tubes *frs_tb;
    t_links      *oldlnk;

    frs_tb = NULL;
    oldlnk = NULL;
    crnt_rm = data->frst_rm;
    while(crnt_rm)
    {
        printf("crn_room %s\n", crnt_rm->name);
        frs_tb = data->frst_tb;
        while(frs_tb)
        {
            if (ft_strequ(crnt_rm->name, frs_tb->first) == 1)
            {
                if (is_same_link(crnt_rm->link, frs_tb->second) == 1)
                {
                    frs_tb = frs_tb->next_tb;
                    continue;
                }
                oldlnk = crnt_rm->link;
                crnt_rm->link = (t_links*)malloc(sizeof(t_links));
                crnt_rm->link->linked_room =
                        found_ptr_room_by_name(data, frs_tb->second);
                crnt_rm->link->next = oldlnk;
                printf("lnk_room %s\n", crnt_rm->link->linked_room->name);
            }
            else if (ft_strequ(crnt_rm->name, frs_tb->second) == 1)
            {
                if (is_same_link(crnt_rm->link, frs_tb->first) == 1)
                {
                    frs_tb = frs_tb->next_tb;
                    continue;
                }
                oldlnk = crnt_rm->link;
                crnt_rm->link = (t_links*)malloc(sizeof(t_links));
                crnt_rm->link->linked_room =
                        found_ptr_room_by_name(data, frs_tb->first);
                crnt_rm->link->next = oldlnk;
                printf("lnk_room %s\n", crnt_rm->link->linked_room->name);
            }
            frs_tb = frs_tb->next_tb;
        }
        crnt_rm = crnt_rm->next_rm;
    }
}

void del_el_val_path(t_vld_path_elem *frs_el)
{
    t_vld_path_elem *crn_fst_el;

    while (frs_el)
    {
        crn_fst_el = frs_el->next;
        free(frs_el);
        frs_el = crn_fst_el;
    }
}
void del_rm_lnks(t_links *rm_lnk)
{
    t_links *mem_rm_lnk;

    while (rm_lnk)
    {
        mem_rm_lnk = rm_lnk->next;
        free(rm_lnk);
        rm_lnk = mem_rm_lnk;
    }
}

void del_rm_from(t_ls_come_from *from)
{
    t_ls_come_from *mem_frm;

    while (from)
    {
        mem_frm = from->next;
        free(from);
        from = mem_frm;
    }
}

void free_mem(t_input_data *data)
{
//    t_lst_vld_path *frs_el;
    t_list_rooms *crn_rm;
    t_list_tubes *crn_tbs;

//    while (lst_vld_path)
//    {
//        frs_el = lst_vld_path->next;
//        del_el_val_path(lst_vld_path->frst_path_el);
//        free(lst_vld_path);
//        lst_vld_path = frs_el;
//    }
    while (data->frst_rm)
    {
        crn_rm = data->frst_rm->next_rm;
        del_rm_from(data->frst_rm->from);
        del_rm_lnks(data->frst_rm->link);
        free(data->frst_rm->name);
        free(data->frst_rm);
        data->frst_rm = crn_rm;
    }
    while (data->frst_tb)
    {
        crn_tbs = data->frst_tb->next_tb;
        free(data->frst_tb->first);
        free(data->frst_tb->second);
        free(data->frst_tb);
        data->frst_tb = crn_tbs;
    }

}

void free_mem_val_path(t_lst_vld_path *lst_vld_path)
{
    t_lst_vld_path *frs_el;

    while (lst_vld_path)
    {
        frs_el = lst_vld_path->next;
        del_el_val_path(lst_vld_path->frst_path_el);
        free(lst_vld_path);
        lst_vld_path = frs_el;
    }
}

int main()
{
    t_input_data data;
    t_lst_vld_path *lst_vld_path;

    data.frst_rm = NULL;
    data.frst_tb = NULL;
    data.cnt_ants = -1;
    if (ft_read_data(&data) == -1 || data.cnt_ants == -1)
    {
        free_mem(&data);
        exit(0);
    }
    add_tubes_to_rooms(&data);
    lst_vld_path = find_valid_path(&data);
    run_ants(&data, lst_vld_path);
    free_mem_val_path(lst_vld_path);
    free_mem(&data);
    return 0;
}