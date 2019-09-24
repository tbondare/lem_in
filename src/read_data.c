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

int		ft_read_data(t_input_data *data)
{
	char	*line;
	int		fd;

//	fd = 0;
	line = NULL;
	fd = open("../t.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if(try_read_cnt_ants(line, data) == 1 ||
				try_read_room(line, data) == 1 ||
				try_read_comment(line, data, fd) == 1 ||
				try_read_tubes(line, data) == 1)
		{
			free(line);
			continue ;
		}
		else
		{
			ft_printf("failed to read tubs %s: room is't defined\n", line);
			free(line);
			exit(1);
		}
	}
	free(line);
	return (0);
}
