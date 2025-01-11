/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:53 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/11 03:34:35 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/* Includes nécessaires */

# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

# include "minilibx-linux/mlx.h"

# include <math.h>
# include <stdlib.h>
# include <stdio.h>

/* Colors for output */
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

/* Définition des constantes */
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define FOV 60
# define MOVE_SPEED 0.08
# define ROTATION_SPEED 0.05
# define PI 3.14159265359
# define TEX_WIDTH 256
# define TEX_HEIGHT 256

# define MINIMAP_SCALE 0.1
# define MINIMAP_WIDTH 256
# define MINIMAP_HEIGHT 256
# define MINIMAP_PLAYER_SIZE 3

# define DOOR_CLOSED 0
# define DOOR_OPEN 1

// Ajouter la structure pour une porte

typedef struct s_door
{
	int		x;
	int		y;
	int		state;
}	t_door;

typedef struct s_animation
{
	int		frame_count;
	int		current_frame;
	double	last_update;
	int		win_frame;
}	t_animation;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_map
{
	int		width;
	int		height;
	char	**fullmap;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		is_map_valid;
	int		all_info;
	t_door	*doors;
	int		nb_doors;
	char	*door_texture;
	char	*wallsmiley1_texture;
	char	*wallsmiley2_texture;
	char	*win_textures[9];
}	t_map;

typedef struct s_minimap_coords
{
	int	center_x;
	int	center_y;
	int	cell_size;
	int	map_x;
	int	map_y;
	int	mini_x;
	int	mini_y;
}	t_minimap_coords;

typedef struct s_draw_line
{
	double	x;
	double	y;
	double	x_inc;
	double	y_inc;
	int		steps;
	int		dir_x;
	int		dir_y;
}	t_draw_line;

typedef struct s_map_iter
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;
}	t_map_iter;

/* Structure pour stocker la minimap */
typedef struct s_minimap {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_minimap;

/* Structure pour stocker une texture */
typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

/* Structure pour stocker toutes les textures */
typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	t_texture	door;
	t_texture	wallsmiley1;
	t_texture	wallsmiley2;
	t_texture	win[9];
}	t_textures;

/* Structure pour stocker les données du joueur */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

/* Structure pour la gestion de la fenêtre et du rendu */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_animation	animation;
	t_player	player;
	t_textures	textures;
	t_map		map;
	t_minimap	*minimap;
	t_keys		keys;
}	t_game;

int			key_press(int keycode, t_game *game);
int			close_window(t_game *game);
int			get_texture_color(t_texture *texture, int x, int y);
void		put_pixel(t_game *game, int x, int y, int color);
int			load_texture(t_game *game, t_texture *texture, char *path);
int			load_textures(t_game *game);
int			is_door_open(t_game *game, int x, int y);
void		display_victory_screen(void);
void		toggle_victory(t_game *game);
int			ft_needs_wall_check(char c);
void		ft_free_win_textures(t_game *game);

/*Parsing*/
void		ft_parsing(int argc, char **argv, t_game *game);
void		ft_get_width_height(t_game *game);
void		ft_struct_map_init(t_game *game);
int			ft_rgb_to_int(int r, int g, int b);
int			ft_is_map_line(t_game *game, char *line);
void		ft_copy_previous_map(char **new_map, char **old_map, int size);
void		ft_map_init(t_game *game, char *argv, int fd);
void		ft_extract_info(t_game *game, char *buff);
int			ft_extract_color(char *buff, t_game *game);
char		*ft_extract_line_info(char *buff, t_game *game);
void		ft_extract_map(t_game *game, char *buff, char **temp);
void		ft_map_check(t_game *game);
void		ft_emptyline_check(t_game *game);
void		ft_wall_check1(t_game *game);
void		ft_wall_check2(t_game *game);
void		ft_wall_check3(t_game *game);
void		ft_invalid_char_check(t_game *game);
void		ft_player_check(t_game *game, int i, int j);
void		ft_free_array(char **array);
void		ft_error_map(char *msg, t_game *game);
void		ft_arg_verif(int argc, char **argv, t_game *game);
int			ft_zero_map_check(char **map, int i, int j);
void		ft_free_textures2(t_game *game);

int			ft_error_handling(t_game *game, char *message);
void		cleanup_game(t_game *game);
void		debug_print_map(t_game *game);
void		destroy_textures(t_game *game);

int			ft_check_texture_prefix(char *buff);
size_t		ft_get_line_length(char *buff);
void		ft_allocate_new_line(t_game *game, size_t len, int i);
void		ft_copy_line(t_game *game, char *buff, size_t len, int i);
void		ft_extract_info2(t_game *game, char *buff);
void		ft_extract_info3(t_game *game, char *buff);
void		ft_extract_info4(t_game *game, char *buff);

/*Init*/
void		init_player_direction2(t_game *game, char direction);
int			init_mlx_window(t_game *game);
int			init_mlx_image(t_game *game);
void		init_game(t_game *game);
void		find_player_position(t_game *game);
int			count_doors(t_game *game);
void		init_doors(t_game *game);
void		init_doors2(t_game *game);
int			load_textures2(t_game *game);
int			load_textures3(t_game *game);
int			load_textures4(t_game *game);

/*Hooks*/
int			key_press(int keycode, t_game *game);
void		handle_forward_backward(int keycode, t_game *game);
void		handle_rotation_right(t_game *game);
void		handle_rotation_left(t_game *game);
void		handle_rotation(int keycode, t_game *game);
void		handle_lateral(int keycode, t_game *game);
int			handle_mouse(int x, int y, t_game *game);
void		init_key_states(t_game *game);
void		update_movement(t_game *game);
int			key_release(int keycode, t_game *game);
void		toggle_door(t_game *game);

/*Raycasting*/
void		init_ray_dir(t_ray *ray, t_game *game, int x);
void		init_ray_pos(t_ray *ray, t_game *game);
void		calc_delta_dist(t_ray *ray);
void		init_step_x(t_ray *ray,	t_game *game);
void		init_step_y(t_ray *ray, t_game *game);
int			check_map_bounds(t_ray *ray, t_game *game);
void		perform_dda_step(t_ray *ray);
void		calc_wall_distance(t_ray *ray, t_game *game);
void		calc_wall_height(t_ray *ray);
void		calc_wall_x(t_ray *ray, t_game *game);
void		calc_texture_x(t_ray *ray);
t_texture	*select_texture(t_ray *ray, t_game *game);
void		draw_wall_line(t_game *game, t_ray *ray, int x, int y);
void		draw_floor_ceiling(t_game *game, t_ray *ray, int x);
void		perform_dda(t_ray *ray, t_game *game);
void		raycasting(t_game *game);
int			render(t_game *game);

/*Minimap*/
void		init_minimap(t_game *game);
void		put_pixel_minimap(t_minimap *minimap, int x, int y, int color);
int			get_cell_color(char cell_type);
void		init_minimap(t_game *game);
void		put_pixel_minimap(t_minimap *minimap, int x, int y, int color);
void		draw_cell_pixels(t_game *game, t_minimap_coords *mc, \
			int px, int py);
void		draw_cell(t_game *game, t_minimap_coords *mc);
void		init_draw_line(t_game *game, t_minimap_coords *mc, t_draw_line *dl);
void		draw_direction(t_game *game, t_minimap_coords *mc);
void		process_cell(t_game *game, t_minimap_coords *mc, t_map_iter *iter);
void		update_map_cells(t_game *game, t_minimap_coords *mc);
void		update_minimap(t_game *game);
void		draw_player(t_game *game, t_minimap_coords *mc);
void		draw_minimap_border(t_game *game, int x, int y,
				int border_thickness);

void		ft_free_map(t_game *game);
void		ft_free_map1(t_game *game);
void		ft_free_textures(t_game *game);

t_texture	*select_special_texture(t_ray *ray, t_game *game);
t_texture	*select_texture(t_ray *ray, t_game *game);

#endif
