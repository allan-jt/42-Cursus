/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:14:31 by athekkep          #+#    #+#             */
/*   Updated: 2022/04/29 15:40:21 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] \
	== '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign = -1;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	free ((char *)str);
	if (i > 5 || num > 255 || sign < 0)
		return (-1);
	return ((int)(num * sign));
}

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_2d(char ***str)
{
	int	i;

	if (!(*str))
		return ;
	i = 0;
	while ((*str)[i])
		free((*str)[i++]);
	free(*str);
	*str = NULL;
}

void	print_error(t_data *data, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	free_all(data);
	exit(EXIT_FAILURE);
}

void	clear_ray_obj(t_data *data, int reinit)
{
	int	i;

	i = -1;
	while (++i < WIDTH)
	{
		data->player.rays[i].obj_num = 0;
		if (data->player.rays[i].obj_direction)
			free (data->player.rays[i].obj_direction);
		if (data->player.rays[i].obj_hit_point)
			free (data->player.rays[i].obj_hit_point);
		if (data->player.rays[i].obj_mag)
			free (data->player.rays[i].obj_mag);
		if (data->player.rays[i].obj_x)
			free (data->player.rays[i].obj_x);
		if (data->player.rays[i].obj_y)
			free (data->player.rays[i].obj_y);
		if (!reinit)
			continue ;
		data->player.rays[i].obj_direction = calloc(1, sizeof(int));
		data->player.rays[i].obj_hit_point = calloc(1, sizeof(int));
		data->player.rays[i].obj_mag = calloc(1, sizeof(int));
		data->player.rays[i].obj_x = calloc(1, sizeof(int));
		data->player.rays[i].obj_y = calloc(1, sizeof(int));
	}
}
