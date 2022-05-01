/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:13:17 by athekkep          #+#    #+#             */
/*   Updated: 2022/04/28 20:13:20 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_to_image(t_data *data, int image, char *path)
{
	data->img[image].img = mlx_xpm_file_to_image(data->mlx, path,
			&data->img[image].width, &data->img[image].hieght);
	if (!data->img[image].img)
		print_error(data, "Couldn't Open Image.. Wrong image path!");
	data->img[image].addr = mlx_get_data_addr(data->img[image].img,
			&data->img[image].bits_per_pixel, &data->img[image].line_length,
			&data->img[image].endian);
}

static void	init_imgs_sprites(t_data *data)
{
	put_to_image(data, DOOR_CLOS, "assets/door1.xpm");
	put_to_image(data, DOOR_CLOS + 1, "assets/door2.xpm");
	put_to_image(data, DOOR_CLOS + 2, "assets/door3.xpm");
	put_to_image(data, DOOR_OPEN, "assets/door4.xpm");
	put_to_image(data, FLAME_FRST, "assets/flame1.xpm");
	put_to_image(data, FLAME_FRST + 1, "assets/flame2.xpm");
	put_to_image(data, FLAME_FRST + 2, "assets/flame3.xpm");
	put_to_image(data, FLAME_FRST + 3, "assets/flame4.xpm");
	put_to_image(data, FLAME_FRST + 4, "assets/flame5.xpm");
	put_to_image(data, FLAME_FRST + 5, "assets/flame6.xpm");
	put_to_image(data, FLAME_FRST + 6, "assets/flame7.xpm");
	put_to_image(data, FLAME_FRST + 7, "assets/flame8.xpm");
	put_to_image(data, FLAME_FRST + 8, "assets/flame9.xpm");
	put_to_image(data, FLAME_FRST + 9, "assets/flame10.xpm");
	put_to_image(data, FLAME_FRST + 10, "assets/flame11.xpm");
	put_to_image(data, FLAME_FRST + 11, "assets/flame12.xpm");
	put_to_image(data, FLAME_FRST + 12, "assets/flame13.xpm");
	put_to_image(data, FLAME_FRST + 13, "assets/flame14.xpm");
	put_to_image(data, FLAME_FRST + 14, "assets/flame15.xpm");
	put_to_image(data, FLAME_FRST + 15, "assets/flame16.xpm");
	put_to_image(data, FLAME_FRST + 16, "assets/flame17.xpm");
	put_to_image(data, FLAME_LAST, "assets/flame18.xpm");
}

void	init_imgs(t_data *data)
{
	data->img[0].img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img[0].addr = mlx_get_data_addr(data->img[0].img,
			&data->img[0].bits_per_pixel, &data->img[0].line_length,
			&data->img[0].endian);
	put_to_image(data, NORTH_TEXT, data->no_path);
	put_to_image(data, SOUTH_TEXT, data->so_path);
	put_to_image(data, WEST_TEXT, data->we_path);
	put_to_image(data, EAST_TEXT, data->ea_path);
	init_imgs_sprites(data);
}

void	init_rays(t_data *data)
{
	int		i;
	double	angle;

	i = -1;
	angle = data->start_angle - ((double) WIDTH * ONE_DEGREE_RAD / 2.0);
	while (++i < WIDTH)
	{
		data->player.rays[i].rot = angle;
		data->player.rays[i].obj_num = 0;
		data->player.rays[i].obj_direction = ft_calloc(1, sizeof(int));
		data->player.rays[i].obj_hit_point = ft_calloc(1, sizeof(int));
		data->player.rays[i].obj_mag = ft_calloc(1, sizeof(int));
		data->player.rays[i].obj_x = ft_calloc(1, sizeof(int));
		data->player.rays[i].obj_y = ft_calloc(1, sizeof(int));
		angle += ONE_DEGREE_RAD;
	}
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	init_imgs(data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
	init_rays(data);
}
