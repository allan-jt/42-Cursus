/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:13:42 by athekkep          #+#    #+#             */
/*   Updated: 2022/04/29 15:35:02 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	void	*dst;

	dst = data->img[0].addr + (y * data->img[0].line_length + x
			* (data->img[0].bits_per_pixel / 8));
	if (!get_t(color))
		*(unsigned int *)dst = color;
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

double	get_ray_distance(t_data *data, int i, int obj)
{
	if (obj >= 0)
		return (data->player.rays[i].obj_mag[obj]
			* cos(fabs(data->player.rays[i].rot
					- data->player.rays[WIDTH / 2].rot)));
	return (data->player.rays[i].mag
		* cos(fabs(data->player.rays[i].rot
				- data->player.rays[WIDTH / 2].rot)));
}

int	img_color(t_data *data, int i, int tex_pos, int obj_index)
{
	t_ray		ray;
	t_image		img;
	int			hit_point;
	int			color;

	ray = data->player.rays[i];
	if (obj_index >= 0)
	{
		img = data->img[ray.obj_direction[obj_index]];
		hit_point = ray.obj_hit_point[obj_index];
	}
	else
	{
		img = data->img[ray.direction];
		hit_point = ray.hit_point;
	}
	color = *(unsigned int *)(img.addr + (tex_pos & (img.hieght - 1))
			* img.line_length + hit_point * img.bits_per_pixel / 8);
	if (!color && obj_index >= 0)
		return (0x10000000);
	return (color);
}

void	init_minimap(t_data *data)
{
	int	position[2];
	int	dimensions[2];

	position[X] = 0;
	position[Y] = 0;
	dimensions[X] = (MM_WIDTH + 3) * 4;
	dimensions[Y] = (MM_HEIGHT + 3) * 4;
	draw_rect(data, position, dimensions, MM_BORDER);
}
