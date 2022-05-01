/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:44:28 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/29 15:45:58 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs/mlx_mac/mlx.h"
# include "libs/libft/libft.h"
# include "libs/gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

/* Game Settings */
# define HEIGHT 768
# define WIDTH 768
# define ROTATION_SPEED 0.04
# define ONE_DEGREE_RAD 0.00116355333
# define BLOCK_SIZE 32
# define SPEED 1

/* Texture Indices */
# define NORTH_TEXT 6
# define SOUTH_TEXT 7
# define WEST_TEXT 8
# define EAST_TEXT 9

/* Minimap */
//# define MM_BKGRND 0x11f0f8ff
# define MM_BORDER 0x00480607
# define MM_GROUND 0x00808080
# define MM_WALL 0x00154360
# define MM_DOOR 0x00FFB129
# define MM_FLAME 0x00299CFF
# define MM_WIDTH 50
# define MM_HEIGHT 50

/* Door sprite */
# define DOOR_CLOS 10
# define DOOR_OPEN 13
# define DOOR_MAP_C 3
# define DOOR_MAP_O 4

/* Flame sprite */
# define FLAME_FRST 14
# define FLAME_LAST 31
# define FLAME_MAP_F 5
# define FLAME_MAP_L 7

/* Linux Keys */
//# define KEY_RIGHT 65363
//# define KEY_LEFT 65361
//# define KEY_W 119
//# define KEY_S 115
//# define KEY_A 97
//# define KEY_D 100
//# define DOORS 101 // E
//# define ESC 65307

/* Miscellaneous */
# define Y 0
# define X 1

/* Mac Keys */
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define DOORS 14
# define ESC 53

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	mag;
	double	rot;
	int		color;
	int		hit_point;
	int		direction;
	int		obj_num;
	int		*obj_hit_point;
	int		*obj_direction;
	int		*obj_mag;
	int		*obj_x;
	int		*obj_y;
}			t_ray;

typedef struct s_player
{
	double			x;
	double			y;
	int				rotate_r;
	int				rotate_l;
	int				move_fw;
	int				move_bw;
	int				strafe_l;
	int				strafe_r;
	struct s_ray	*rays;
}					t_player;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		hieght;
}				t_image;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	struct s_image	img[32];
	struct s_player	player;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				c_color;
	int				f_color;
	int				map_width;
	int				map_height;
	int				config_fd;
	double			start_angle;
	int				index;
	int				wrong_door;
	int				c_color_count;
	int				f_color_count;
	char			**map;
}				t_data;

/* cub3d.c */
void	add_asset_to_image(t_data *data, int x, int y, int asset);
void	init_rays_mag(t_data *data);

/* draw_shapes.c */
void	draw_player(t_data *data, int x, int y, int r);
void	draw_rect(t_data *data, int *position, int *dimensions, int color);

/* draw.c */
void	draw_3d(t_data *data, int i);
void	print_map(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	add_asset_to_image(t_data *data, int x, int y, int asset);

/* draw_utils.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_t(int trgb);
double	get_ray_distance(t_data *data, int i, int obj);
int		img_color(t_data *data, int i, int tex_pos, int obj_index);
void	init_minimap(t_data *data);

/* ray_caster.c */
void	check_line(t_data *data);
int		insdie_wall(t_data *data, int x, int y, int i);

/* interaction.c */
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		mouse_rotate(int key, int x, int y, t_data *data);

/* render.c */
int		render(t_data *data);

/* data_init.c */
void	data_init(t_data *data);
void	init_imgs(t_data *data);
void	init_rays(t_data *data);

/* move_player.c */
void	rotate(t_data *data, int dir, int i);
void	move(t_data *data, int dir);

/* parser.c */
void	check_map_name(t_data *data, int argc, char **argv);
void	validate_map_contents(t_data *data);
int		parse_map(t_data *data, int argc, char **argv);

/* map_contents.c */
void	check_player_pos(t_data *data, char c, int *x);
int		contain_walls_or_spaces_only(char	*temp);
void	check_if_closed_by_walls(t_data *data);
void	validate_door(t_data *data, int i, int j, int x);
void	check_if_valid_doors(t_data *data);

/* map_elements.c */
int		read_color(t_data *data, char **split_line, char type);
int		handle_color(t_data *data, char **split_line);
int		handle_elements(t_data *data, char **split_line);
void	check_elements(t_data *data);

/* parse_map.c */
void	read_map(t_data *data, char **line, char **map_input);
void	parse_map_contents(t_data *data);

/* parser_utils.c */
char	*create_spaces(t_data *data, int number);
void	resize_width(t_data *data);
void	calc_map_width_height(t_data *data);

/* validate_map.c */
void	check_chars(t_data *data);
int		check_if_no_more_map(t_data *data);
void	check_spaces(t_data *data, int i, int j);
void	check_spaces_from_all_dir(t_data *data);

/* objectc.c */
int		obj_status(t_data *data, int x, int y, int to_do);
void	change_door_status(t_data *data, int count);
void	change_flame_status(t_data *data, int count);
void	door_status(t_data *data);

/* sprite.c */
void	raycast_sprite(t_data *data, int i, int *pos);
void	store_sprite(t_data *data, int hitpoint, double mag, int *pos);

/* utils.c */
void	clear_ray_obj(t_data *data, int reinit);
void	print_error(t_data *data, char *msg);
void	free_2d(char ***str);
int		ft_strlen_2d(char **str);
int		color_atoi(const char *str);

/* exit.c */
int		close_window(t_data *data);
void	free_all(t_data *data);
void	check_player_pos(t_data *data, char c, int *x);

#endif