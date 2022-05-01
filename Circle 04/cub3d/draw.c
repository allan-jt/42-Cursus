/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:13:30 by athekkep          #+#    #+#             */
/*   Updated: 2022/04/30 09:04:57 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_obj(t_data *data, int i, int obj_index)
{
	double	height;
	int		draw[2];
	double	inc;
	double	tex_pos;

	height = (BLOCK_SIZE * HEIGHT) / get_ray_distance(data, i, obj_index);
	draw[0] = -height / 2 + (HEIGHT / 2);
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = (height / 2) + (HEIGHT / 2);
	inc = (float)data->img[data->player.rays[i].obj_direction[obj_index]].hieght
		/ height;
	tex_pos = (draw[0] - HEIGHT / 2 + height / 2) * inc;
	while (draw[0] < draw[1] && draw[0] < HEIGHT)
	{
		my_mlx_pixel_put(data, i, draw[0]++,
			img_color(data, i, (int)tex_pos, obj_index));
		tex_pos += inc;
	}
}

void	draw_3d(t_data *data, int i)
{
	double	height;
	int		draw[3];
	double	inc;
	double	tex_pos;

	height = (BLOCK_SIZE * HEIGHT) / get_ray_distance(data, i, -1);
	draw[0] = -height / 2 + (HEIGHT / 2);
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = (height / 2) + (HEIGHT / 2);
	inc = (float)data->img[data->player.rays[i].direction].hieght / height;
	tex_pos = (draw[0] - HEIGHT / 2 + height / 2) * inc;
	while (draw[0] < draw[1] && draw[0] < HEIGHT)
	{
		my_mlx_pixel_put(data, i, draw[0]++,
			img_color(data, i, (int)tex_pos, -1));
		tex_pos += inc;
	}
	draw[2] = data->player.rays[i].obj_num;
	while (draw[2]-- > 0)
		draw_obj(data, i, draw[2]);
}

void	draw_floor_cel(t_data *data)
{
	int	position[2];
	int	dimensions[2];

	position[X] = 0;
	position[Y] = 0;
	dimensions[X] = WIDTH;
	dimensions[Y] = HEIGHT / 2;
	draw_rect(data, position, dimensions, data->c_color);
	position[Y] = HEIGHT / 2;
	draw_rect(data, position, dimensions, data->f_color);
}

void	draw_minimap(t_data *data, int i)
{
	int	pos[2];
	int	start_draw[2];
	int	dimensions[2];

	pos[Y] = i;
	pos[X] = -1;
	dimensions[X] = 4;
	dimensions[Y] = 4;
	if (!(abs(pos[Y] - (int)data->player.y / BLOCK_SIZE) <= MM_HEIGHT / 2))
		return ;
	start_draw[Y] = (25 + (pos[Y] - (int)data->player.y / BLOCK_SIZE)) * 4;
	while (data->map[pos[Y]][++pos[X]])
	{
		if (!(abs(pos[X] - (int)data->player.x / BLOCK_SIZE) < MM_WIDTH / 2))
			continue ;
		start_draw[X] = (25 + (pos[X] - (int)data->player.x / BLOCK_SIZE)) * 4;
		if (data->map[pos[Y]][pos[X]] == '0')
			draw_rect(data, start_draw, dimensions, MM_GROUND);
		if (data->map[pos[Y]][pos[X]] == '1')
			draw_rect(data, start_draw, dimensions, MM_WALL);
		if (data->map[pos[Y]][pos[X]] == '3')
			draw_rect(data, start_draw, dimensions, MM_DOOR);
		if (data->map[pos[Y]][pos[X]] == '5')
			draw_rect(data, start_draw, dimensions, MM_FLAME);
	}
}

void	print_map(t_data *data)
{
	int	i;
	int	position[2];
	int	dimensions[2];

	mlx_clear_window(data->mlx, data->win);
	draw_floor_cel(data);
	check_line(data);
	i = -1;
	while (++i < WIDTH)
		draw_3d(data, i);
	i = -1;
	init_minimap(data);
	while (data->map[++i])
		draw_minimap(data, i);
	position[X] = MM_WIDTH * 4 / 2;
	position[Y] = MM_HEIGHT * 4 / 2;
	dimensions[X] = 4;
	dimensions[Y] = 4;
	draw_rect(data, position, dimensions, 0x00FFEEFF);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0].img, 0, 0);
}
