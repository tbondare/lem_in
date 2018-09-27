//
// Created by tanya on 15.09.18.
//

#ifndef LEM_IN_LIBFTLEMIN_H
#define LEM_IN_LIBFTLEMIN_H

# include"libft/libft.h"

typedef struct s_room
{
    char *name;
    int x;
    int y;
    int is_sart;
    int is_end;
}t_room;

typedef struct s_list_rooms
{
    t_room room;
    struct s_list_rooms *next_rm;
}t_list_rooms;

typedef struct s_tube
{
    char *first;
    char *second;
}t_tube;

typedef struct s_list_tubes
{
    t_tube tube;
    struct s_list_tubes *next_tb;
}t_list_tubes;

typedef struct s_input_data
{
    int cnt_ants;
    t_list_rooms *frst_rm;
    t_list_tubes *frst_tb;

}t_input_data;

typedef struct s_vld_path_elem
{
   char *name;
   struct s_vld_path_elem *next;
}t_vld_path_elem;

typedef struct s_lst_vld_path
{
    int leng;
    t_vld_path_elem *first_path_el;
    struct s_lst_vld_path *next;
}t_lst_vld_path;

typedef struct s_list_queue
{
    char *crn_room_name;
    struct s_list_queue *next;
}t_list_queue;

int ft_read_data(t_input_data *data);
t_lst_vld_path *find_valid_path(t_input_data data);

#endif //LEM_IN_LIBFTLEMIN_H