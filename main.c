#include "libftlemin.h"
//#include "stdio.h"

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

void add_tubes_to_rooms(t_input_data *data)
{
    t_list_rooms *crnt_rm;
    t_list_tubes *frs_tb;
    t_links      *oldlnk;

    crnt_rm = data->frst_rm;
    while(crnt_rm)
    {
//        printf("crn_room %s\n", crnt_rm->name);
        frs_tb = data->frst_tb;
        while(frs_tb)
        {
            if (ft_strequ(crnt_rm->name, frs_tb->first) == 1)
            {
                oldlnk = crnt_rm->link;
                crnt_rm->link = (t_links*)malloc(sizeof(t_links));
                crnt_rm->link->linked_room =
                        found_ptr_room_by_name(data, frs_tb->second);
                crnt_rm->link->next = oldlnk;
//                printf("lnk_room %s\n", crnt_rm->link->linked_room->name);
            }
            else if (ft_strequ(crnt_rm->name, frs_tb->second) == 1)
            {
                oldlnk = crnt_rm->link;
                crnt_rm->link = (t_links*)malloc(sizeof(t_links));
                crnt_rm->link->linked_room =
                        found_ptr_room_by_name(data, frs_tb->first);
                crnt_rm->link->next = oldlnk;
//                printf("lnk_room %s\n", crnt_rm->link->linked_room->name);
            }
            frs_tb = frs_tb->next_tb;
        }
        crnt_rm = crnt_rm->next_rm;
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
        //TODO:error;
        return (0);
    }
    add_tubes_to_rooms(&data);
    lst_vld_path = find_valid_path(&data);
    run_ants(&data, lst_vld_path);
    return 0;
}