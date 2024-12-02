/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:53 by dmathis           #+#    #+#             */
/*   Updated: 2024/11/18 14:15:14 by dloisel          ###   ########.fr       */
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

/* Définition des constantes */
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define FOV 60
#define MOVE_SPEED 0.1
#define ROTATION_SPEED 0.05
#define PI 3.14159265359
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

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

/* Structure pour stocker toutes les textures */
typedef struct s_textures {
    t_texture north;
    t_texture south;
    t_texture east;
    t_texture west;
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

/* Structure pour la gestion de la fenêtre et du rendu */
typedef struct s_game {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    t_player player;
    t_textures textures;
    int **map;
    int map_width;
    int map_height;
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


#endif