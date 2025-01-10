/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:32:57 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 23:17:22 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	draw_wall_line(t_game *game, t_ray *ray, int x, int y)
{
	double		step;
	double		tex_pos;
	int			tex_y;
	int			color;
	t_texture	*texture;

	texture = select_texture(ray, game);
	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_texture_color(texture, ray->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(game, x, y, color);
		y++;
	}
}

void	draw_floor_ceiling(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(game, x, y, game->map.ceiling_color);
		y++;
	}
	y = ray->draw_end;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(game, x, y, game->map.floor_color);
		y++;
	}
}

void    perform_dda(t_ray *ray, t_game *game)
{
    ray->hit = 0;
    while (ray->hit == 0)
    {
        perform_dda_step(ray);
        if (!check_map_bounds(ray, game))
            break ;
        
        // Ajout du debug
        if (game->map.fullmap[ray->map_x][ray->map_y] == 'X')
        {
            printf("Found X at position [%d][%d]\n", ray->map_x, ray->map_y);
        }

        if (game->map.fullmap[ray->map_x][ray->map_y] == '1'
            || game->map.fullmap[ray->map_x][ray->map_y] == 'T'
            || (game->map.fullmap[ray->map_x][ray->map_y] == 'D'
            && !is_door_open(game, ray->map_x, ray->map_y))
            || game->map.fullmap[ray->map_x][ray->map_y] == 'X')  // Ajout de X ici
            ray->hit = 1;
    }
}

void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray_dir(&ray, game, x);
		init_ray_pos(&ray, game);
		calc_delta_dist(&ray);
		init_step_x(&ray, game);
		init_step_y(&ray, game);
		perform_dda(&ray, game);
		calc_wall_distance(&ray, game);
		calc_wall_height(&ray);
		calc_wall_x(&ray, game);
		calc_texture_x(&ray);
		draw_wall_line(game, &ray, x, 0);
		draw_floor_ceiling(game, &ray, x);
		x++;
	}
}

int	render(t_game *game)
{
	game->animation.frame_count++;
	update_movement(game);
	raycasting(game);
	mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	update_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->minimap->img, 10, 10);
	usleep(10000);
	return (0);
}
