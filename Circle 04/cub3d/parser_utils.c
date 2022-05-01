/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:24:40 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 20:07:02 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*create_spaces(t_data *data, int number)
{
	char	*res;
	int		i;

	i = 0;
	if (number > 0)
	{
		res = malloc(sizeof(char) * (number + 1));
		if (!res)
			print_error(data, "Malloc Error!");
	}
	else
		return (NULL);
	while (i < number)
		res[i++] = ' ';
	res[i] = '\0';
	return (res);
}

void	resize_width(t_data *data)
{
	int		i;
	int		width;
	char	*spaces;

	i = 0;
	while (data->map[i])
	{
		width = ft_strlen(data->map[i]);
		if (width < data->map_width)
		{
			spaces = create_spaces(data, data->map_width - width);
			data->map[i] = ft_strjoin(data->map[i], spaces);
			free(spaces);
		}
		i++;
	}
}

void	calc_map_width_height(t_data *data)
{
	int	i;

	i = 0;
	data->map_width = 0;
	data->map_height = 0;
	data->map_width = ft_strlen(data->map[i]);
	while (data->map[i])
	{
		if ((int)ft_strlen(data->map[i]) > data->map_width)
			data->map_width = ft_strlen(data->map[i]);
		i++;
	}
	data->map_height = i;
	data->player.rays = ft_calloc(WIDTH, sizeof(struct s_ray));
	if (!data->player.rays)
		print_error(data, "Malloc Error!");
}
