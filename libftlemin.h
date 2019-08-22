//
// Created by tanya on 15.09.18.
//

#ifndef LEM_IN_LIBFTLEMIN_H
#define LEM_IN_LIBFTLEMIN_H

# include"libft/libft.h"
# include <stdlib.h>

struct s_links;
struct s_ls_come_from;

typedef struct s_list_rooms
{
    char *name;
    int x;
    int y;
    int is_sart;
    int is_end;
    int was_in_room;
    int is_in_queue;
    int is_in_val_pth;
    struct s_links *link;
    struct s_ls_come_from *from;
    struct s_list_rooms *next_rm;
}t_list_rooms;

typedef struct s_ls_come_from
{
    struct s_list_rooms *room;
    struct s_ls_come_from *next;
}t_ls_come_from;

typedef struct s_links
{
    t_list_rooms *linked_room;
    struct s_links *next;
}t_links;

typedef struct s_list_tubes
{
    char *first;
    char *second;
    struct s_list_tubes *next_tb;
}t_list_tubes;

typedef struct s_input_data
{
    int flg_ants;
    int cnt_ants;
    char *end_room_name;
    t_list_rooms *frst_rm;
    t_list_tubes *frst_tb;

}t_input_data;

typedef struct s_vld_path_elem
{
   t_list_rooms *room;
   struct s_vld_path_elem *next;
}t_vld_path_elem;

typedef struct s_lst_vld_path
{
    int leng;
    int y;
    int x;
    t_vld_path_elem *frst_path_el;
    struct s_lst_vld_path *next;
}t_lst_vld_path;

typedef struct s_list_queue
{
    t_list_rooms *crn_room;
    struct s_list_queue *next;
}t_list_queue;

typedef struct s_queue_data
{
    t_list_queue *frst_queue_el;
    t_list_queue *mem_queue;
    t_list_queue *last_q_el;
}t_queue_data;

typedef struct s_out_room
{
    char *name;
    int ant_index;
}t_out_room;

typedef struct s_out_path
{
    int nmb_ants;
    int path_leng;
    t_out_room *path;
}t_out_path;

typedef struct s_output_data
{
    int nmb_paths;
    t_out_path *arr_paths;
}t_output_data;

int ft_read_data(t_input_data *data);
t_lst_vld_path *find_valid_path(t_input_data *data);
void run_ants(t_input_data *data, t_lst_vld_path *lst_vld_path);

#endif //LEM_IN_LIBFTLEMIN_H