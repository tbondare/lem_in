#include "libftlemin.h"

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
    find_valid_path(data);
    return 0;
}