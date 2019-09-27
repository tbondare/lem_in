#include "./inc/libftlemin.h"

t_lst_vld_path	*add_val_path(t_lst_vld_path **frst_vl_pth)
{
	t_lst_vld_path *mem_vld_path;
	t_lst_vld_path *new_vld_path;

	if (*frst_vl_pth == NULL)
	{
		new_vld_path = (t_lst_vld_path*)malloc(sizeof(t_lst_vld_path));
		*frst_vl_pth = new_vld_path;
	}
	else
	{
		mem_vld_path = *frst_vl_pth;
		while (mem_vld_path->next)
			mem_vld_path = mem_vld_path->next;
		mem_vld_path->next = (t_lst_vld_path*)malloc(sizeof(t_lst_vld_path));
		new_vld_path = mem_vld_path->next;
	}
	new_vld_path->y = 0;
	new_vld_path->x = 0;
	new_vld_path->next = NULL;
	new_vld_path->frst_path_el = NULL;
	new_vld_path->leng = 1;
	return (new_vld_path);
}

t_path			*create_path_for_queue(t_input_data *data)
{
	t_path		*path;
	t_for_del	*del;

	path = (t_path*)malloc(sizeof(t_path));
	path->vertex = find_start_room(data);
	path->prev = NULL;
	del = data->del_path;
	data->del_path = (t_for_del*)malloc(sizeof(t_for_del));
	data->del_path->next = del;
	data->del_path->path = path;
	return (path);
}

t_path			*add_room_to_path(t_input_data *data, t_path *path,
									t_list_rooms *room)
{
	t_path		*mem_path;
	t_for_del	*del;

	mem_path = path;
	room->cnt_was_in_room++;
	path = (t_path*)malloc(sizeof(t_path));
	path->prev = mem_path;
	path->vertex = room;
	del = data->del_path;
	data->del_path = (t_for_del*)malloc(sizeof(t_for_del));
	data->del_path->next = del;
	data->del_path->path = path;
	return (path);
}

void	free_path(t_input_data *data)
{
	t_for_del *del;

	del = data->del_path;
	while (del)
	{
		data->del_path = data->del_path->next;
		free(del->path);
		free(del);
		del = data->del_path;
	}
}