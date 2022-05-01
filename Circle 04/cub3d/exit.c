/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:42:02 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 12:42:03 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	free_all(data);
	exit(EXIT_SUCCESS);
}

void	free_text(t_data *data)
{
	if (data->no_path)
		free(data->no_path);
	if (data->so_path)
		free(data->so_path);
	if (data->we_path)
		free(data->we_path);
	if (data->ea_path)
		free(data->ea_path);
}

void	free_imgs(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 32)
		if (data->img[i].img)
			mlx_destroy_image(data->mlx, data->img[i].img);
}

void	free_all(t_data *data)
{
	obj_status(data, 0, 0, 1);
	if (!data)
		return ;
	if (data->player.rays)
	{
		clear_ray_obj(data, 0);
		free(data->player.rays);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->map)
		free_2d(&(data->map));
	free_imgs(data);
	free_text(data);
	if (data->mlx)
		free(data->mlx);
	free(data);
}
