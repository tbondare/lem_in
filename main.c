#include "libftlemin.h"

int main()
{
    t_input_data data;

    data.frst_rm = NULL;
    data.frst_tb = NULL;
    data.cnt_ants = -1;
    if (ft_read_data(&data) == -1)
    {
        //TODO:error;
        return (0);
    }
    return 0;
}