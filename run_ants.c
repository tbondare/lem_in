#include "libftlemin.h"
#include "stdio.h"

int ft_round(float x)
{
    
    return (x);
}

void cnt_x(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
    int n;
    int prdct_b;
    int sum_y;
    float x_
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
}

void run_ants(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
    cnt_x(data, lst_vld_path);
}
