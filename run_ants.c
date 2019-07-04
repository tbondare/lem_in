#include "libftlemin.h"
#include "stdio.h"

int ft_round(float x)
{
    int x_int;
    int c;

    x_int = x;
    x = x - x_int;
    while (x)
    {
        c = x * 10;
        if (c >= 5)
            return (++x_int);
        if (c < 4)
            return (x_int);
        x = x - c;
    }
    return (x_int);
}

int cnt_x_for_every_valpath(t_input_data *data, t_lst_vld_path *lst_vld_path, t_output_data *out)
{
    int n;
    int prdct_b;
    int sum_y;
    t_lst_vld_path *crnt;

    n = 0;
    sum_y = 0;
    prdct_b = 1;
    crnt = lst_vld_path;
    while (crnt)
    {
        n++;
        prdct_b = prdct_b * crnt->leng;
        crnt = crnt->next;
    }
    printf("n = %d\n", n);
    crnt = lst_vld_path;
    while (crnt)
    {
        crnt->y = prdct_b / crnt->leng;
        sum_y = sum_y + crnt->y;
        crnt = crnt->next;
    }
    crnt = lst_vld_path;
    while (crnt)
    {
        crnt->x = ft_round((float)data->cnt_ants * crnt->y / sum_y);
        printf("x = %d\n", crnt->x);
        crnt = crnt->next;
    }
    return (prdct_b);
}

void run_ants(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
    t_output_data out;
    cnt_x_for_every_valpath(data, lst_vld_path, &out);
}
