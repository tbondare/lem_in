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

int cnt_x_for_every_valpath(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
    int prdct_b;
    int sum_y;
    int nmbr_path;
    t_lst_vld_path *crnt;

    sum_y = 0;
    prdct_b = 1;
    crnt = lst_vld_path;
    nmbr_path = 0;
    while (crnt)
    {
        nmbr_path++;
        prdct_b = prdct_b * crnt->leng;
        crnt = crnt->next;
    }
    printf("n = %d\n", nmbr_path);
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
        crnt->x = ft_round((float) data->cnt_ants * crnt->y / sum_y);
        printf("x = %d\n", crnt->x);
        crnt = crnt->next;
    }
    return (nmbr_path);
}

void output_ants(t_output_data *out)
{

}

void run_ants(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
    int i;
    int j;
    int nmbr_path;
    t_output_data out;
    t_lst_vld_path *crnt;

    i = 0;
    j = 0;
    crnt = lst_vld_path;
    nmbr_path = cnt_x_for_every_valpath(data, lst_vld_path);
    out.output = (t_output_data*)malloc(sizeof(t_output_data) * nmbr_path);
    while (crnt)
    {
        out.output->arr = (char*)malloc(sizeof(char) * crnt->leng);
        out.output->arr[i] = (char*)malloc(sizeof(char));
        while (crnt->frst_path_el)
        {
            out.output->arr[j] = crnt->frst_path_el->room;
            out.output->nmb_ants = crnt->x;
            crnt->frst_path_el = crnt->frst_path_el->next;
            j++;
        }
        i++;
        crnt = crnt->next;
    }
//    output_ants(out.output);
}
