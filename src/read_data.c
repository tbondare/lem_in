/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:48:56 by tbondare          #+#    #+#             */
/*   Updated: 2019/09/20 15:30:26 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"
#include <fcntl.h>

void	free_frst_tb(t_input_data *data)
{
	t_list_tubes *next;

	ft_strdel(&data->frst_tb->first);
	ft_strdel(&data->frst_tb->second);
	next = data->frst_tb->next_tb;
	free(data->frst_tb);
	data->frst_tb = next;
}

void add_line_to_input(t_str_list **input, char *line)
{
	t_str_list *mem_input;

	if(*input == NULL)
	{
		*input = (t_str_list*)malloc(sizeof(t_str_list));
		(*input)->line = line;
		(*input)->next = NULL;
	}
	else
	{
		mem_input = *input;
		while (mem_input && mem_input->next)
			mem_input = mem_input->next;
		mem_input->next = (t_str_list*)malloc(sizeof(t_str_list));
		mem_input->next->line = line;
		mem_input->next->next = NULL;
	}
}

void ft_print_input_str(t_str_list *input)
{
	t_str_list *mem_input;

	mem_input = input;
	while(mem_input)
	{
		ft_printf("%s\n", mem_input->line);
		mem_input = mem_input->next;
	}
	while(input)
	{
		free(input->line);
		mem_input = input;
		input = input->next;
		free(mem_input);
	}
}

int		ft_read_data(t_input_data *data)
{
	char	*line;
	int		fd;
	t_str_list *input;

//	fd = 0;
	line = NULL;
	input = NULL;
	fd = open("../input_data2.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		add_line_to_input(&input, line);
		if(try_read_cnt_ants(line, data) == 1 ||
				try_read_room(line, data) == 1 ||
				try_read_comment(line, data, fd, &input) == 1 ||
				try_read_tubes(line, data) == 1)
			continue ;
		else
		{
			ft_printf("failed to read tubs %s: room is't defined\n", line);
			free(line);
			exit(1);
		}
	}
	free(line);
	ft_print_input_str(input);
	ft_printf("\n");
	return (0);
}
