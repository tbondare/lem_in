//
// Created by tanya on 15.09.18.
//

#ifndef LEM_IN_LIBFTLEMIN_H
#define LEM_IN_LIBFTLEMIN_H

# include"libft/libft.h"

struct s_links;

/*typedef struct s_room
{
    char *name;
    int x;
    int y;
    int is_sart;
    int is_end;
    struct s_links *link;
    int was_in_room;
}t_room; */

/*typedef struct s_links
{
    t_rooms *linked_room;
    struct s_links *next;
}t_links;*/

typedef struct s_list_rooms
{
//  t_room room;
    char *name;
    int x;
    int y;
    int is_sart;
    int is_end;
    int was_in_room;
    struct s_links *link;
    struct s_list_rooms *next_rm;
}t_list_rooms;

typedef struct s_links
{
    t_list_rooms *linked_room;
    struct s_links *next;
}t_links;

//typedef struct s_tube
//{
//    char *first;
//    char *second;
//}t_tube;

typedef struct s_list_tubes
{
//  t_tube tube;
    char *first;
    char *second;
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

typedef struct s_queue_data
{
    t_list_queue *frst_queue_el;
    t_list_queue *mem_queue;
    t_list_queue *last_q_el;
}t_queue_data;

int ft_read_data(t_input_data *data);
t_lst_vld_path *find_valid_path(t_input_data data);

#endif //LEM_IN_LIBFTLEMIN_H