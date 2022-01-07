/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 08:55:19 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/15 13:48:51 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
	{
		printf("Error\nInvalid number of args\n");
		return (1);
	}
	vars.bonus = 1;
	vars.count = 0;
	vars.mlx = mlx_init();
	vars.map = m_to_a(argv[1], &vars);
	img_init(&vars.img, &vars);
	img_init_bonus(&vars.img, &vars);
	img_init_enemy(&vars.img, &vars);
	map_init(&vars, &vars.img, vars.map);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_player, &vars);
	mlx_hook(vars.win, 17, 1L << 2, closes, &vars);
	mlx_loop(vars.mlx);
	free_map(vars.map);
}
