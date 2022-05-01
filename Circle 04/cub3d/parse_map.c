/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:11:09 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 20:06:21 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(t_data *data, char **line, char **map_input)
{
	while (1)
	{
		*line = get_next_line(data->config_fd);
		if (!*line)
			print_error(data, "Wrong Config File");
		if (*line[0] == '\n')
		{
			free(*line);
			continue ;
		}
		else
		{
			*map_input = *line;
			break ;
		}
		free(*line);
	}
}

void	parse_map_contents(t_data *data)
{
	char	*line;
	char	*map_input;

	read_map(data, &line, &map_input);
	while (1)
	{
		line = get_next_line(data->config_fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			if (check_if_no_more_map(data))
			{
				free(map_input);
				print_error(data, "Wrong Config File");
			}
			break ;
		}
		map_input = ft_strjoin(map_input, line);
		free(line);
	}
	data->map = ft_split(map_input, '\n');
	free(map_input);
	calc_map_width_height(data);
}
