/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:12:58 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 20:08:31 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_chars(t_data *data)
{
	int		i;
	int		j;
	int		x;
	char	c;

	i = 0;
	x = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			c = data->map[i][j];
			check_player_pos(data, c, &x);
			j++;
		}
		i++;
	}
	if (x != 1)
		print_error(data, "Map Includes Non or more than 1 starting pos!");
}

int	check_if_no_more_map(t_data *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(data->config_fd);
		if (!line)
			return (0);
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		else
		{
			free(line);
			return (1);
		}
		free(line);
	}
}

void	check_spaces(t_data *data, int i, int j)
{
	if (i + 1 < data->map_height)
		if (data->map[i + 1][j] != ' ' && data->map[i + 1][j] != '1')
			print_error(data, "Map Not Closed by walls!");
	if (i - 1 >= 0)
		if (data->map[i - 1][j] != ' ' && data->map[i - 1][j] != '1')
			print_error(data, "Map Not Closed by walls!");
	if (j + 1 < data->map_width)
		if (data->map[i][j + 1] != ' ' && data->map[i][j + 1] != '1')
			print_error(data, "Map Not Closed by walls!");
	if (j - 1 >= 0)
		if (data->map[i][j - 1] != ' ' && data->map[i][j - 1] != '1')
			print_error(data, "Map Not Closed by walls!");
}

void	check_spaces_from_all_dir(t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		temp = data->map[i];
		while (data->map[i][j])
		{
			if (temp[j] == ' ')
				check_spaces(data, i, j);
			j++;
		}
		i++;
	}
}
