/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:53 by dmathis           #+#    #+#             */
/*   Updated: 2024/12/23 00:42:28 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* Includes nécessaires */

# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

#include "minilibx-linux/mlx.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GAME_STATE_MENU 0
#define GAME_STATE_PLAYING 1
#define GAME_STATE_GAMEOVER 2
#define INITIAL_TIME 180  // 3 minutes en secondes
#define FOG_INTERVAL 5   // 1.5 minutes en secondes
#define MAX_FOG_LEVELS 8  // Nombre de paliers de brouillard
#define BASE_VIEW_DISTANCE 20.0  // Distance de vue de base

/* Colors for output */
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

/* Définition des constantes */
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define FOV 60
#define MOVE_SPEED 0.025
#define ROTATION_SPEED 0.02
#define PI 3.14159265359
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define MINIMAP_SCALE 0.2
#define MINIMAP_WIDTH (WINDOW_WIDTH * 0.25)
#define MINIMAP_HEIGHT (WINDOW_HEIGHT * 0.25)
#define MINIMAP_PLAYER_SIZE 3
#define MINIMAP_BLUR_RADIUS 2
#define MINIMAP_BLUR_SIGMA 1.0

#define MESSAGE_DURATION 100

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

/* Structure pour stocker une texture */
typedef struct s_texture {
	void *img;
	int *data;
	int width;
	int height;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_texture;

typedef struct s_minimap {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
} t_minimap;

/* Structure pour stocker toutes les textures */
typedef struct s_textures {
	t_texture north;
	t_texture south;
	t_texture east;
	t_texture west;
	t_texture key;
	t_texture door;
} t_textures;

/* Structure pour stocker les données du joueur */
typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_inventory {
    int keys;           
    int show_message;   
    int message_timer;
} t_inventory;

/* Structure pour la gestion de la fenêtre et du rendu */
typedef struct s_game {
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int move_forward;    // W
	int move_backward;   // S
	int move_left;       // A
	int move_right;      // D
	int rotate_left;     // Flèche gauche
	int rotate_right;    // Flèche droite
	int bits_per_pixel;
	int line_length;
	int endian;
	int game_state;
	time_t start_time;
	time_t current_time;
	int fog_level;       // Niveau actuel de brouillard (0 à MAX_FOG_LEVELS)
	double view_distance; // Distance de vue actuelle
	float fog_intensity;
	t_player player;
	t_textures textures;
	t_map map;
	t_minimap	*minimap;
	t_inventory inventory;
} t_game;

extern int default_map[8][8];


void init_game(t_game *game);
int key_press(int keycode, t_game *game);
int close_window(t_game *game);
int get_texture_color(t_texture *texture, int x, int y);
void put_pixel(t_game *game, int x, int y, int color);
int load_texture(t_game *game, t_texture *texture, char *path);
int load_textures(t_game *game);
int render(t_game *game);
int key_release(int keycode, t_game *game);
void move_player(t_game *game);

void draw_menu(t_game *game);
void draw_gameover(t_game *game);
void draw_timer(t_game *game);
void update_game_state(t_game *game);
int blend_color(int color1, int color2, double factor);

/*Parsing*/
void	ft_parsing(int argc, char **argv, t_game *game);
void	ft_get_width_height(t_game *game);
void	ft_struct_map_init(t_game *game);
int		ft_rgb_to_int(int r, int g, int b);
int		ft_is_map_line(char *line);
void	ft_copy_previous_map(char **new_map, char **old_map, int size);
void	ft_map_init(t_game *game, char *argv, int fd);
void	ft_extract_info(t_game *game, char *buff);
int		ft_extract_color(char *buff, t_game *game);
char	*ft_extract_line_info(char *buff, t_game *game);
void	ft_extract_map(t_game *game, char *buff, int j, char **temp);
void	ft_map_check(t_game *game);
void	ft_emptyline_check(t_game *game);
void	ft_wall_check1(t_game *game);
void	ft_wall_check2(t_game *game);
void	ft_wall_check3(t_game *game);
void	ft_invalid_char_check(t_game *game);
void	ft_player_check(t_game *game, int i, int j);
void	ft_free_array(char **array);
void	ft_error_map(char *msg, t_game *game);
void	ft_free_map(t_game *game);
void	ft_arg_verif(int argc, char **argv, t_game *game);
int		ft_zero_map_check(char **map, int i, int j);

int		ft_error_handling(t_game *game, char *message);
void 	cleanup_game(t_game *game);
void 	debug_print_map(t_game *game);
void 	destroy_textures(t_game *game);

void 	init_minimap(t_game *game);
void	update_minimap(t_game *game);

void 	init_inventory(t_game *game);
void 	collect_key(t_game *game, int map_x, int map_y);
void 	try_open_door(t_game *game);
void 	draw_inventory(t_game *game);

void 	draw_key(t_game *game, int map_x, int map_y, double dist);

#endif
