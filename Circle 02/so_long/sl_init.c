/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:19:44 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/08 13:19:46 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	img_init(t_imgs *img, t_vars *vars)
{
	img->bhole.path = "./images/bhole.xpm";
	img->bhole.img = mlx_xpm_file_to_image(vars->mlx, img->bhole.path,
			&(img->bhole.width), &(img->bhole.height));
	img->space.path = "./images/space.xpm";
	img->space.img = mlx_xpm_file_to_image(vars->mlx, img->space.path,
			&(img->space.width), &(img->space.height));
	img->astroid.path = "./images/astroid.xpm";
	img->astroid.img = mlx_xpm_file_to_image(vars->mlx, img->astroid.path,
			&(img->astroid.width), &(img->astroid.height));
	img->collect.path = "./images/collect.xpm";
	img->collect.img = mlx_xpm_file_to_image(vars->mlx, img->collect.path,
			&(img->collect.width), &(img->collect.height));
	img->player[0].path = "./images/player1.xpm";
	img->player[0].img = mlx_xpm_file_to_image(vars->mlx, img->player[0].path,
			&(img->player[0].width), &(img->player[0].height));
}

void	img_init_bonus(t_imgs *img, t_vars *vars)
{
	img->player[1].path = "./images/player2.xpm";
	img->player[1].img = mlx_xpm_file_to_image(vars->mlx, img->player[1].path,
			&(img->player[1].width), &(img->player[1].height));
	img->player[2].path = "./images/player3.xpm";
	img->player[2].img = mlx_xpm_file_to_image(vars->mlx, img->player[2].path,
			&(img->player[2].width), &(img->player[2].height));
	img->player[3].path = "./images/player4.xpm";
	img->player[3].img = mlx_xpm_file_to_image(vars->mlx, img->player[3].path,
			&(img->player[3].width), &(img->player[3].height));
	img->player[4].path = "./images/player5.xpm";
	img->player[4].img = mlx_xpm_file_to_image(vars->mlx, img->player[4].path,
			&(img->player[4].width), &(img->player[4].height));
	img->player[5].path = "./images/player6.xpm";
	img->player[5].img = mlx_xpm_file_to_image(vars->mlx, img->player[5].path,
			&(img->player[5].width), &(img->player[5].height));
	img->player[6].path = "./images/player7.xpm";
	img->player[6].img = mlx_xpm_file_to_image(vars->mlx, img->player[6].path,
			&(img->player[6].width), &(img->player[6].height));
}

void	img_init_enemy(t_imgs *img, t_vars *vars)
{
	img->enemy[0].path = "./images/enemy1.xpm";
	img->enemy[0].img = mlx_xpm_file_to_image(vars->mlx, img->enemy[0].path,
			&(img->enemy[0].width), &(img->enemy[0].height));
	img->enemy[1].path = "./images/enemy2.xpm";
	img->enemy[1].img = mlx_xpm_file_to_image(vars->mlx, img->enemy[1].path,
			&(img->enemy[1].width), &(img->enemy[1].height));
	img->enemy[2].path = "./images/enemy3.xpm";
	img->enemy[2].img = mlx_xpm_file_to_image(vars->mlx, img->enemy[2].path,
			&(img->enemy[2].width), &(img->enemy[2].height));
	img->enemy[3].path = "./images/enemy4.xpm";
	img->enemy[3].img = mlx_xpm_file_to_image(vars->mlx, img->enemy[3].path,
			&(img->enemy[3].width), &(img->enemy[3].height));
	img->enemy[4].path = "./images/enemy5.xpm";
	img->enemy[4].img = mlx_xpm_file_to_image(vars->mlx, img->enemy[4].path,
			&(img->enemy[4].width), &(img->enemy[4].height));
}

void	map_init(t_vars *vars, t_imgs *img, char **map)
{
	int	wt;
	int	ht;

	ht = vars->m_ht;
	while (ht-- > 0)
	{
		wt = -1;
		while (map[ht][++wt] != '\0')
			map_put(vars, img, wt, ht);
	}
}
