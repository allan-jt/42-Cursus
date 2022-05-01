/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_contents.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:54 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 22:20:42 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_player_pos(t_data *data, char c, int *x)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W' \
	&& c != 'E' && c != ' ' && c != '3' && c != '5')
		print_error(data, "Map Includes NON-allowed chars!");
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		*x = *x + 1;
		if (c == 'N')
			data->start_angle = -1.57080001;
		if (c == 'S')
			data->start_angle = 1.57080001;
		if (c == 'W')
			data->start_angle = 2.0 * 1.57080001;
	}
}

int	contain_walls_or_spaces_only(char *temp)
{
	int	j;

	j = 0;
	while (temp[j])
	{
		if (temp[j] != '1' && temp[j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

void	check_if_closed_by_walls(t_data *data)
{
	int		i;
	int		x;
	char	*temp;

	i = 0;
	x = 0;
	while (data->map[i])
	{
		temp = ft_strtrim(data->map[i], " ");
		if (temp[0] != '1' || temp[ft_strlen(temp) - 1] != '1')
			x = 1;
		if (i == 0)
			if (contain_walls_or_spaces_only(temp))
				x = 1;
		if (i == (data->map_height - 1))
			if (contain_walls_or_spaces_only(temp))
				x = 1;
		i++;
		free(temp);
		if (x == 1)
			print_error(data, "Map Not Closed by walls!");
	}
}

void	validate_door(t_data *data, int i, int j, int x)
{
	if (i + 1 < data->map_height && i - 1 >= 0)
		if (data->map[i + 1][j] == '1' \
		&& data->map[i - 1][j] == '1')
			x++;
	if (j + 1 < data->map_width && j - 1 >= 0)
		if (data->map[i][j + 1] == '1' \
		&& data->map[i][j - 1] == '1')
			x++;
	if (x == 0)
		print_error(data, "Wrong Door Postion!");
}

void	check_if_valid_doors(t_data *data)
{
	int		i;
	int		j;
	int		x;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			x = 0;
			if (data->map[i][j] == '3')
			{
				validate_door(data, i, j, x);
			}
		}
	}
}
