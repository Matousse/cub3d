/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:53 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 16:29:49 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# include "/home/dmathis/42cursus/42_utils/mlx/mlx.h"

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

typedef struct s_bag
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		map;
	t_camera	camera;
}				t_bag;

//	Functions

// Initialization

void	init_game(t_bag *bag);
void	init2(t_bag *bag);

// Main

void	render_frame(t_bag *bag);
int		key_press(int keycode, t_bag *bag);
int		game_loop(t_bag *bag);
int		main(void);

// End
int		close_window(t_bag *bag);

#endif
