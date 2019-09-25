/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftlemin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 16:04:18 by tbondare          #+#    #+#             */
/*   Updated: 2019/09/17 14:06:38 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LIBFTLEMIN_H
# define LEM_IN_LIBFTLEMIN_H

# include "./libft/inc/libft.h"
# include "./libft/ft_printf/inc/libftprintf.h"
# include <stdlib.h>
# include <stdio.h>

struct s_links;
struct s_ls_come_from;

typedef struct s_str_list
{
	char *line;
	struct s_str_list *next;
}t_str_list;

typedef struct				s_list_rooms
{
	char					*name;
	int						x;
	int						y;
	int						is_sart;
	int						is_end;
	int						is_in_val_pth;
	struct s_links			*link;
	struct s_ls_come_from	*from;
	struct s_list_rooms		*next_rm;
}							t_list_rooms;

typedef struct				s_ls_come_from
{
	struct s_list_rooms		*room;
	struct s_ls_come_from	*next;
}							t_ls_come_from;

typedef struct				s_links
{
	t_list_rooms			*linked_room;
	struct s_links			*next;
}							t_links;

typedef struct				s_list_tubes
{
	char					*first;
	char					*second;
	struct s_list_tubes		*next_tb;
}							t_list_tubes;

typedef struct				s_input_data
{
	int						flg_ants;
	int						cnt_ants;
	char					*end_room_name;
	t_list_rooms			*frst_rm;
	t_list_tubes			*frst_tb;
}							t_input_data;

typedef struct				s_vld_path_elem
{
	t_list_rooms			*room;
	int						i;
	struct s_vld_path_elem	*next;
}							t_vld_path_elem;

typedef struct				s_lst_vld_path
{
	int						leng;
	int						y;
	int						x;
	t_vld_path_elem			*frst_path_el;
	struct s_lst_vld_path	*next;
}							t_lst_vld_path;

typedef struct s_path
{
	t_list_rooms *vertex;
	struct s_path *prev;
}t_path;

typedef struct				s_list_queue
{
	t_path *path;
	struct s_list_queue		*next;
}							t_list_queue;

typedef struct				s_queue_data
{
	t_list_queue			*frst_queue_el;
	t_list_queue			*mem_queue;
	t_list_queue			*last_q_el;
}							t_queue_data;

typedef struct				s_out_room
{
	char					*name;
	int						ant_index;
}							t_out_room;

typedef struct				s_out_path
{
	int						nmb_ants;
	int						path_leng;
	t_out_room				*path;
}							t_out_path;

typedef struct				s_output_data
{
	int						nmb_paths;
	t_out_path				*arr_paths;
}							t_output_data;


t_list_rooms				*find_start_room(t_input_data *data);
void						add_queue_el(t_queue_data *que, t_path *el_que);
void						del_first_queue_el(t_queue_data *queue);
void						add_come_from_room(t_list_rooms *come_from_rm,
		t_list_rooms *crnt_rm);
void						del_queue(t_queue_data *queue);

void						whl_f_save_vl_path(t_list_rooms *crn_room);
void						save_val_path(t_lst_vld_path **frst_vl_pth,
        t_path *crn, t_input_data *data);
void						els_f_whl_fnd_vl_path(t_links *crn_rm_ln,
		t_queue_data **queue);
void						whl_f_find_val_path(t_input_data *data,
		t_links *crn_rm_ln,
		t_queue_data *queue, t_lst_vld_path **frst_vl_pth);
t_lst_vld_path				*find_valid_path(t_input_data *data);

void						del_el_val_path(t_vld_path_elem *frs_el);
void						del_rm_lnks(t_links *rm_lnk);
void						del_rm_from(t_ls_come_from *from);
void						free_mem(t_input_data *data);
void						free_mem_val_path(t_lst_vld_path *lst_vld_path);

t_list_rooms				*found_ptr_room_by_name(t_input_data *data,
		char *name);
int							is_same_link(t_links *lnk, char *name);
void						helper_f_add_tbs(t_input_data *data,
		t_list_tubes *frs_tb, t_list_rooms **crnt_rm);
void						add_tubes_to_rooms(t_input_data *data);
int							main(void);

void						init_room(char *line, t_input_data *data);
void						add_new_rm(t_input_data *data, t_list_rooms **new);
void						add_rm_to_list(t_input_data *data);
int							is_room_exist(t_input_data *data, char *name_rm);
void						add_tb_to_list(t_input_data *data);

int							try_read_cnt_ants(char *line, t_input_data *data);
int							try_read_room(char *line, t_input_data *data);
int							try_read_tubes (char *line, t_input_data *data);
int							try_read_comment(char *line, t_input_data *data,
		int fd);

void						free_frst_tb(t_input_data *data);
int							ft_read_data(t_input_data *data);

int							ft_round(float x);
void						round_ants(t_input_data *data,
		t_lst_vld_path **crnt, int sum_y);
int							cnt_x_for_every_valpath(t_input_data *data,
		t_lst_vld_path *lst_vld_path);
void						move_ants(t_output_data *out);
void						push_ants (t_input_data *data, t_output_data *out,
		int *ant_ind);

int							print_ants(t_output_data *out);
void						output_ants(t_input_data *data, t_output_data *out);
void						del_arr_path(t_output_data *out);
void						inner_whl_f_run_ants(t_vld_path_elem *crnt_el,
		t_output_data *out, int *j);
void						run_ants(t_input_data *data,
		t_lst_vld_path *lst_vld_path);
#endif
