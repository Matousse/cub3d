/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:53 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 23:51:28 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define NUM_TEXTURES 2

# include "/home/dmathis/42cursus/42_utils/mlx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.03

// Structures

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
}				t_map;

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

typedef struct s_bag
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_texture	textures[6];
	t_map		map;
	t_camera	camera;
}				t_bag;

//	Functions

// Initialization

void			init_game(t_bag *bag);
void			init2(t_bag *bag);

// Main

int				key_press(int keycode, t_bag *bag);
int				game_loop(t_bag *bag);
int				main(void);

// End
int				close_window(t_bag *bag);
void			free_textures(t_bag *bag);

// Textures

void			load_texture(t_bag *bag, int index, char *path);

// Raytracing

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

#endif
