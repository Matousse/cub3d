/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:53 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 22:09:36 by dmathis          ###   ########.fr       */
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

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.03
# define NUM_TEXTURES 2

# define KEY_W 119 // 'w'
# define KEY_S 115 // 's'
# define KEY_A 97  // 'a'
# define KEY_D 100 // 'd'
# define KEY_ESC 65307

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
	double		fov;
}				t_camera;

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

typedef struct s_ray_info
{
	t_vector	dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			side;
}				t_ray_info;

typedef struct s_map
{
	int			width;
	int			height;
	char **fullmap;    /* Complete map including walls and spaces */
	char *no_texture;  /* Path to north texture */
	char *so_texture;  /* Path to south texture */
	char *we_texture;  /* Path to west texture */
	char *ea_texture;  /* Path to east texture */
	int floor_color;   /* RGB color for floor */
	int ceiling_color; /* RGB color for ceiling */
	int player_x;      /* Player starting X position */
	int player_y;      /* Player starting Y position */
	char player_dir;   /* Initial player direction (N/S/E/W) */
	int is_map_valid;  /* Map validation flag */
	int all_info;      /* Flag for all required info present */
}				t_map;

typedef struct s_bag
{
	void *mlx;             /* MLX instance pointer */
	void *win;             /* Window pointer */
	void *img;             /* Current frame image pointer */
	char *addr;            /* Current frame data address */
	int bits_per_pixel;    /* Bits per pixel for current frame */
	int line_length;       /* Line length for current frame */
	int endian;            /* Endian for current frame */
	t_texture no_texture;  /* North wall texture */
	t_texture so_texture;  /* South wall texture */
	t_texture we_texture;  /* West wall texture */
	t_texture ea_texture;  /* East wall texture */
	t_texture textures[6]; /* Array of additional textures */
	t_map map;             /* Game map data */
	t_camera camera;       /* Player camera data */
}				t_bag;

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
void			ft_mlx_init(t_bag *game);
void			ft_init_texture(t_bag *game);
t_texture		ft_load_texture(t_bag *game, char *file_path);
void			ft_game_init(t_bag *game);
void			init_game(t_bag *bag);
void			init2(t_bag *bag);
void			ft_init_player(t_bag *game);
int				ft_init_mlx(t_bag *game);
void			ft_struct_init(t_bag *game);

/* Load textures*/
int				ft_load_all_textures(t_bag *game);

/* Game Loop and Events */
int				game_loop(t_bag *bag);
int				key_press(int keycode, t_bag *bag);
int				close_window(t_bag *bag);

/* Raycasting Functions */
void			my_mlx_pixel_put(t_bag *bag, int x, int y, int color);
void			calculate_ray_dir(t_bag *bag, int x, t_vector *ray_dir);
void			init_dda(t_bag *bag, t_vector *ray_dir, t_vector *side_dist,
					t_vector *delta_dist);
int				perform_dda(t_bag *bag, t_vector *ray_dir, t_vector *side_dist,
					t_vector *delta_dist);
double			calculate_perp_wall_dist(t_bag *bag, t_vector *ray_dir,
					int side, int map_x, int map_y);
void			draw_vertical_line(t_bag *bag, int x, int draw_start,
					int draw_end, int color);
void			cast_single_ray(t_bag *bag, int x);
void			cast_rays(t_bag *bag);
void			draw_textured_line(t_bag *bag, int x, t_ray_info *ray);

/* Texture Management */
t_texture		ft_load_texture(t_bag *game, char *path);
void			free_textures(t_bag *bag);

/* End */

void			ft_cleanup(t_bag *game);
int				ft_init_mlx(t_bag *game);
void			ft_cleanup(t_bag *game);
t_texture		ft_load_texture(t_bag *game, char *path);
void			draw_textured_line(t_bag *bag, int x, t_ray_info *ray);
unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y);
int				close_window(t_bag *bag);

void			ft_get_player_pos(t_bag *game);

#endif
