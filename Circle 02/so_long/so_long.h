/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:18:05 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/16 14:57:27 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
# include "libft/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>

typedef struct s_data {
	void	*img;
	char	*path;
	int		width;
	int		height;
}				t_data;

typedef struct s_imgs {
	t_data	bhole;
	t_data	space;
	t_data	astroid;
	t_data	collect;
	t_data	player[7];
	t_data	enemy[5];
}				t_imgs;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	char	**map;
	int		m_ht;
	int		m_wt;
	t_imgs	img;
	int		count;
	int		bonus;
}				t_vars;

void	print_steps(int steps, t_vars *var);
void	quit(t_vars *vars, int err);
int		find_obj(char **map, char obj);
int		*find_obj_cord(char **map, char obj);
int		emy(char map, t_vars *vars);
void	map_valid(char **map, t_vars *vars);
void	map_type(char *file, t_vars *vars);
char	**m_to_a(char *file, t_vars *vars);
void	img_init(t_imgs *img, t_vars *vars);
void	img_init_bonus(t_imgs *img, t_vars *vars);
void	img_init_enemy(t_imgs *img, t_vars *vars);
void	map_init(t_vars *vars, t_imgs *img, char **map);
void	map_put(t_vars *vars, t_imgs *img, int wt, int ht);
void	move(int *p, t_vars *vars, t_imgs *img, char **map);
int		key_hook(int keycode, t_vars *vars);
int		closes(t_vars *vars);
void	map_exist(int fd, t_vars *vars, char *str);
void	free_all(t_vars *vars);
void	free_map(char **map);

#endif
