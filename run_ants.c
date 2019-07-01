#include "libftlemin.h"
#include "stdio.h"

char *write_float_in_str(float x)
{
    int x_int;
    char *str;
    char *str2;

    if (x < 1)
    {
        str = (char*)malloc(sizeof(char) * 3);
        str[0] = '0';
        str[1] = ',';
        str[2] = '\0';
    }
    else
    {
        x_int = x;
        str = ft_itoa(x_int);
        str2 = (char*)malloc(sizeof(char) * 2);
        str2[0] = ',';
        str2[1] = '\0';
        str = ft_strjoin(str, str2);
        free(str2);
        x_int = x;
        x = x - x_int;
    }
    while (x)
    {
        x_int = x;
        x = x - x_int;
        x = x * 10;
        str2 = (char*)malloc(sizeof(char) * 2);
        str2[0] = x_int + '0';
        str2[1] = '\0';
        str = ft_strjoin(str, str2);
        free(str2);
    }
    return (str);
}

int ft_round(float x)
{
    int i;
    int cnt_dgt;
    char *arr_dgt;

    i = 0;
    if (x == 0)
        return (0);
    write_float_in_str(x);
    return (x);
}

void cnt_x(t_input_data *data, t_lst_vld_path *lst_vld_path)
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
}

void run_ants(t_input_data *data, t_lst_vld_path *lst_vld_path)
{
    cnt_x(data, lst_vld_path);
}
