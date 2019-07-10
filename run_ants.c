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

void move_ants(t_output_data *out)
{
    int i;
    int j;

    i = 0;
    while (i < out->nmb_paths)
    {
        j = out->arr_paths[i].path_leng - 1;
        while (j > 0)
        {
            out->arr_paths[i].path[j].ant_index = out->arr_paths[i].path[j - 1].ant_index;
            j--;
        }
        i++;
    }
}

void push_ants (t_input_data *data,t_output_data *out, int *ant_ind)
{
    int i;

    i = 0;
    while (i < out->nmb_paths)
    {
        if (*ant_ind <= data->cnt_ants)
            out->arr_paths[i].path[0].ant_index = (*ant_ind)++;
        else
            out->arr_paths[i].path[0].ant_index = 0;
        i++;
    }
}

int print_ants(t_output_data *out)
{
    int i;
    int j;
    int flg;

    i = 0;
    flg = 0;
    while (i < out->nmb_paths)
    {
        j = out->arr_paths[i].path_leng - 1;
        while (j >= 0)
        {
            if (out->arr_paths[i].path[j].ant_index != 0)
            {
                printf("L%d-%s ", out->arr_paths[i].path[j].ant_index, out->arr_paths[i].path[j].name);
                flg = 1;
            }
            j--;
        }
        i++;
    }
    printf("\n");
    return (flg);
}

void output_ants(t_input_data *data,t_output_data *out)
{
    int flg;
    int ant_ind;

    flg = 1;
    ant_ind = 1;
    while (flg == 1)
    {
        move_ants(out);
        push_ants(data, out, &ant_ind);
        flg = print_ants(out);
    }
}

void run_ants(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
    int i;
    int j;
    t_output_data out;
    t_lst_vld_path *crnt;
    t_vld_path_elem *crnt_el;

    i = 0;
    crnt = lst_vld_path;
    out.nmb_paths = cnt_x_for_every_valpath(data, lst_vld_path);
    out.arr_paths = (t_out_path*)malloc(sizeof(t_out_path) * out.nmb_paths);
    while (crnt)
    {
        crnt_el = crnt->frst_path_el;
        out.arr_paths[i].path = (t_out_room*)malloc(sizeof(t_out_room) * crnt->leng);
        j = 0;
        while (crnt_el)
        {
            out.arr_paths[i].path[j].name = crnt_el->room->name;
            out.arr_paths[i].path[j].ant_index = 0;
            out.arr_paths[i].nmb_ants = crnt->x;
            out.arr_paths[i].path_leng = crnt->leng;
            crnt_el = crnt_el->next;
            j++;
        }
        out.arr_paths[i].path[j].name = data->end_room_name;
        out.arr_paths[i].path[j].ant_index = 0;
        i++;
        crnt = crnt->next;
    }
    output_ants(data,&out);
}
