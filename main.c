#include "libftlemin.h"

void add_tubes_to_rooms(t_input_data *data)
{
    t_list_rooms *crnt_rm;
    t_list_tubes *frs_tb;

    crnt_rm = data->frst_rm;
    while(crnt_rm)
    {
        frs_tb = data->frst_tb;
        while(frs_tb)
        {
            if (ft_strequ (crnt_rm->name, frs_tb->first) == 1)
            {
                crnt_rm->link = (t_links*)malloc(sizeof(t_links));
                crnt_rm->link->linked_room->link = frs_tb->second;
                crnt_rm = crnt_rm->link->next;
            }
            else if (ft_strequ (data->frst_rm->name, frs_tb->second) == 1)
            {
                crnt_rm->link = (t_links*)malloc(sizeof(t_links));
                crnt_rm->link->linked_room->link = frs_tb->first;
                crnt_rm = crnt_rm->link->next;
            }
            frs_tb = frs_tb->next_tb;
        }
        crnt_rm = crnt_rm->next_rm;
    }
}

int main()
{
    t_input_data data;

    data.frst_rm = NULL;
    data.frst_tb = NULL;
    data.cnt_ants = -1;
    if (ft_read_data(&data) == -1 || data.cnt_ants == -1)
    {
        //TODO:error;
        return (0);
    }
    add_tubes_to_rooms(&data);
    find_valid_path(data);
    return 0;
}