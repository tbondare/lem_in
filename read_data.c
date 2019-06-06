#include "libftlemin.h"
# include <fcntl.h>

int try_read_cnt_ants(char *line, t_input_data *data)
{
    int i;

    i = 0;
    while (line[i] != '\0' && ft_isdigit(line[i]) == 1)
        i++;
    if (line[i] == '\0')
    {
        data->cnt_ants = ft_atoi(line);
        return (1);
    }
    return (0);
}

void init_room(char *line, t_input_data *data)
{
    int i;

    i = 0;
    while (line[i] != '\0' && line[i] != ' ')
        i++;
    data->frst_rm->name = ft_strsub(line, 0, i);
    data->frst_rm->x = ft_atoi(&line[++i]);
    while (line[i] != '\0' && line[i] != ' ')
        i++;
    data->frst_rm->y = ft_atoi(&line[++i]);
}

void add_rm_to_list(t_input_data *data)
{
    t_list_rooms *new;

    if (data->frst_rm == NULL)
    {
        data->frst_rm = (t_list_rooms*)malloc(sizeof(t_list_rooms));
        data->frst_rm->name = NULL;
        data->frst_rm->x = 0;
        data->frst_rm->y = 0;
        data->frst_rm->is_sart = 0;
        data->frst_rm->is_end = 0;
        data->frst_rm->was_in_room = 0;
        data->frst_rm->is_in_queue = 0;
        data->frst_rm->is_in_val_pth = 0;
        data->frst_rm->link = NULL;
        data->frst_rm->from = NULL;
        data->frst_rm->next_rm = NULL;
    }
    else
    {
        new = (t_list_rooms*)malloc(sizeof(t_list_rooms));
        new->name = NULL;
        new->x = 0;
        new->y = 0;
        new->is_sart = 0;
        new->is_end = 0;
        new->was_in_room = 0;
        new->is_in_queue = 0;
        new->is_in_val_pth = 0;
        new->link = NULL;
        new->from = NULL;
        new->next_rm = data->frst_rm;
        data->frst_rm = new;
    }
}

int try_read_room(char *line, t_input_data *data)
{
    int i;

    i = 0;
    if (line[0] == '#' || line[0] == 'L')
        return (0);
    while (line[i] != '\0' && line[i] != ' ')
        i++;
    if (line[i] != ' ' || (ft_isdigit(line[i + 1]) == 0 && line[i] != '-'))
        return (0);
    i = i + 2;
    while (line[i] != '\0' && ft_isdigit(line[i]) == 1)
        i++;
    if (line[i] != ' ' || (ft_isdigit(line[i + 1]) == 0 && line[i] != '-'))
        return (0);
    i = i + 2;
    while (line[i] != '\0' && ft_isdigit(line[i]) == 1)
        i++;
    if (line[i] == '\0')
    {
        add_rm_to_list(data);
        init_room(line, data);
        return (1);
    }
    return (0);
}

int find_same_room(t_input_data *data, char *name_rm)
{
    int cnt;
    t_list_rooms *cur_rm;

    cnt =0;
    cur_rm = data->frst_rm;
    while (cur_rm != NULL)
    {
        if (ft_strequ(name_rm, cur_rm->name) == 1)
            cnt++;
        cur_rm = cur_rm->next_rm;
    }
    if(cnt == 0)
        return (0);
    return (1);
}

void add_tb_to_list(t_input_data *data)
{
    t_list_tubes *new;

    if (data->frst_tb == NULL)
    {
        data->frst_tb = (t_list_tubes*)malloc(sizeof(t_list_tubes));
        data->frst_tb->first = NULL;
        data->frst_tb->second = NULL;
        data->frst_tb->next_tb = NULL;
    }
    else
    {
        new = (t_list_tubes*)malloc(sizeof(t_list_tubes));
        new->first = NULL;
        new->second = NULL;
        new->next_tb = data->frst_tb;
        data->frst_tb = new;
    }
}

void free_frst_tb(t_input_data *data)
{
    t_list_tubes *next;

    ft_strdel(&data->frst_tb->first);
    ft_strdel(&data->frst_tb->second);
    next = data->frst_tb->next_tb;
    free(data->frst_tb);
    data->frst_tb = next;
}

int try_read_tubes (char *line, t_input_data *data)
{
    int i;
    char *name_rm;

    i = 0;
    if (line[0] == '#' || line[0] == 'L')
        return (0);
    while (line[i] != '\0' && line[i] != '-')
        i++;
    if (line[i] != '-')
        return (0);
    name_rm = ft_strsub(line, 0, i);
    if (find_same_room(data, name_rm) == 0)
        return (-1);
    add_tb_to_list(data);
    data->frst_tb->first = name_rm;
    i++;
    name_rm = ft_strsub(line, i, ft_strlen(&line[i]));
    if (find_same_room(data, name_rm) == 0)
    {
        free_frst_tb(data);
        free(name_rm);
        return (-1);
    }
    data->frst_tb->second = name_rm;
    return (1);
}

int try_read_comment(char *line, t_input_data *data, int fd)
{
    char fl;

    if (line[0] != '#')
        return (0);
    if (ft_strcmp(line, "##start") != 0 && ft_strcmp(line, "##end") != 0)
        return (1);
    fl = line[2];
    if (get_next_line(fd, &line) <= 0)
        return (-1);
    if (try_read_room(line, data) != 1)
        return (-1);
    if (fl == 's')
        data->frst_rm->is_sart = 1;
    else
        data->frst_rm->is_end = 1;
    return (1);
}

int ft_read_data(t_input_data *data)
{
    char *line;
    int i;
    int fd;

    fd = open("input_data.txt", O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        if (try_read_cnt_ants(line, data) == 1)
            continue ;
        if (try_read_room(line, data) == 1)
            continue ;
        i = try_read_tubes(line, data);
        if (i == 1)
            continue ;
        else if (i == -1)
            return (-1);
        if (try_read_comment(line, data, fd) == 1)
            continue ;
        return (-1);
    }
    return (0);
}
