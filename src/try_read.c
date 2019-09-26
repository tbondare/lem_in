/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:56:24 by tbondare          #+#    #+#             */
/*   Updated: 2019/08/31 17:55:42 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/libftlemin.h"

int	try_read_cnt_ants(char *line, t_input_data *data)
{
	int i;

	i = 0;
	while (line[i] != '\0' && ft_isdigit(line[i]) == 1)
		i++;
	if (line[i] == '\0' && i > 0)
	{
		data->cnt_ants = ft_atoi(line);
		if (data->cnt_ants == 0)
		{
			free(line);
			ft_printf("ants quantity = 0\n");
			exit(1);
		}
		return (1);
	}
	else if (line[i] == '\0' && i == 0)
	{
		free(line);
		ft_printf("failed to read ants quantity\n");
		exit(1);
	}
	return (0);
}

int	try_read_room(char *line, t_input_data *data)
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

int	try_read_tubes(char *line, t_input_data *data)
{
	int		i;
	char	*name_rm;

	i = 0;
	if (line[0] == '#' || line[0] == 'L')
		return (0);
	while (line[i] != '\0' && line[i] != '-')
		i++;
	if (line[i] != '-')
		return (0);
	name_rm = ft_strsub(line, 0, i);
	if (is_room_exist(data, name_rm) == 0)
		return (-1);
	add_tb_to_list(data);
	data->frst_tb->first = name_rm;
	i++;
	name_rm = ft_strsub(line, i, ft_strlen(&line[i]));
	if (is_room_exist(data, name_rm) == 0)
	{
		free_frst_tb(data);
		free(name_rm);
		return (-1);
	}
	data->frst_tb->second = name_rm;
	return (1);
}

char* loop_comments(int fd, t_str_list **input)
{
	char	*line;

	while(get_next_line(fd, &line) > 0)
	{
		add_line_to_input(input, line);
		if (line[0] != '#')
			return (line);
	}
	free(line);
	ft_printf("Failed to read string after ##start or ##end\n");
	exit(1);
}

int	try_read_comment(char *line, t_input_data *data, int fd, t_str_list **input)
{
	char fl;

	if (line[0] != '#')
		return (0);
	if (ft_strcmp(line, "##start") != 0 && ft_strcmp(line, "##end") != 0)
		return (1);
	fl = line[2];
	line = loop_comments(fd, input);
	if (try_read_room(line, data) != 1)
	{
		free(line);
		ft_printf("Failed to read room after ##start or ##end\n");
		exit(1);
	}
	if (fl == 's')
		data->frst_rm->is_sart = 1;
	else
		data->frst_rm->is_end = 1;
	return (1);
}
