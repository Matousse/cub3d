/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:53 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 03:46:55 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* A faire :

Parsing

Mettre game.map.is_map_valid à 1 si la map est validée, et à 0 sinon

*/

/* ************************************************************************** */
/*                                  INCLUDES                                    */
/* ************************************************************************** */

# include "/home/dmathis/42cursus/42_utils/mlx/mlx.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                  DEFINES                                     */
/* ************************************************************************** */

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.03
# define NUM_TEXTURES 2

# define FOV 60
# define PI 3.14159265359

# define KEY_W 119 // 'w'
# define KEY_S 115 // 's'
# define KEY_A 97  // 'a'
# define KEY_D 100 // 'd'
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Colors for output */
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

/* ************************************************************************** */
/*                                 STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_camera
{
	t_vector	position;
	t_vector	direction;
	t_vector	plane;
	double		move_speed;
	double		rot_speed;
}				t_camera;

typedef struct s_map
{
	int			width;
	int			height;
	char		**fullmap;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
	int			player_x;
	int			player_y;
	char		player_dir;
	int			is_map_valid;
	int			all_info;
}				t_map;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

typedef struct s_bag
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_texture	no_texture;
	t_texture	so_texture;
	t_texture	we_texture;
	t_texture	ea_texture;
	t_map		map;
	t_camera	camera;
}				t_bag;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

/* ************************************************************************** */
/*                                PROTOTYPES                                    */
/* ************************************************************************** */

/* Parsing Functions */
void			ft_parsing(int argc, char **argv, t_bag *game);
void			ft_error_map(char *msg, t_bag *game);
void			ft_arg_verif(int argc, char **argv, t_bag *game);
void			ft_map_init(t_bag *game, char *argv, int fd);
int				ft_is_map_line(char *line);
int				ft_rgb_to_int(int r, int g, int b);
void			ft_copy_previous_map(char **new_map, char **old_map, int size);
void			ft_free_map(t_bag *game);
void			ft_map_check(t_bag *game);
int				ft_space_map_check(char **map, int i, int j);
int				ft_zero_map_check(char **map, int i, int j);
void			ft_player_check(t_bag *game, int i, int j);
void			ft_free_array(char **array);

/* Initialization Functions */

void			ft_struct_init(t_bag *game);
int				ft_init_mlx(t_bag *game);
void			ft_init_camera(t_bag *game);
int				ft_init_player(t_bag *game);
int				ft_find_player_pos(t_bag *game);
int				ft_is_player(char c);

/* Game Loop and Events */

int				ft_game_loop(t_bag *game);

/* Raycasting Functions */

void			ft_clear_image(t_bag *game);
void			ft_put_pixel(t_bag *game, int x, int y, int color);
void			ft_init_camera(t_bag *game);
void			ft_raycasting(t_bag *game);
void			ft_init_ray(t_bag *game, t_ray *ray, int x);
void			ft_calculate_step(t_bag *game, t_ray *ray);
void			ft_perform_dda(t_bag *game, t_ray *ray);
void			ft_calculate_wall(t_bag *game, t_ray *ray);
void			ft_draw_wall(t_bag *game, t_ray *ray, int x);

/* Texture Management */
void			ft_draw_wall(t_bag *game, t_ray *ray, int x);
int				ft_get_texture_color(t_texture *texture, int tex_x, int tex_y);
t_texture		*ft_select_texture(t_bag *game, t_ray *ray);
void			ft_draw_texture(t_bag *game, t_ray *ray, int x, int y);
int				ft_load_texture(t_bag *game, t_texture *texture, char *path);
int				ft_load_textures(t_bag *game);

/* Movements*/

void			ft_move_forward(t_bag *game);
void			ft_move_backward(t_bag *game);
void			ft_move_left(t_bag *game);
void			ft_move_right(t_bag *game);
void			ft_rotate_left(t_bag *game);
void			ft_rotate_right(t_bag *game);

/* Hooks */

void			ft_setup_hooks(t_bag *game);
int				ft_close_window(t_bag *game);
int				ft_key_press(int keycode, t_bag *game);

/* End */

void			ft_cleanup_textures(t_bag *game);
void			ft_cleanup(t_bag *game);
int				ft_error_handling(t_bag *game, char *message);
int				close_window(t_bag *bag);
#endif
