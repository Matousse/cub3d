/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 03:25:16 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/31 15:32:15 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_texture	ft_load_texture(t_bag *game, char *file_path)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(game->mlx, file_path, &texture.width, \
	&texture.height);
	if (!texture.img)
	{
		ft_printf(RED "%s\n", "Error");
		ft_printf("%s%s%s\n", "Couldn't load the texture at '", \
		file_path, "' does it exist ?"RESET);
		ft_error_handling(game, NULL);
	}
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, \
	&texture.line_length, &texture.endian);
	return (texture);
}

void	ft_init_texture(t_bag *game)
{
	if (game->map.is_map_valid == 1)
		return ;
	game->no_texture = ft_load_texture(game, game->map.no_texture);
	game->so_texture = ft_load_texture(game, game->map.so_texture);
	game->we_texture = ft_load_texture(game, game->map.we_texture);
	game->ea_texture = ft_load_texture(game, game->map.ea_texture);
}

void	ft_draw_texture(t_bag *game, t_ray *ray, int x, int y)
{
	t_texture	*texture;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			color;

	// Sélectionner la texture en fonction de la direction du mur
	texture = ft_select_texture(game, ray);
	// Calculer la position x exacte où le rayon a touché le mur
	if (ray->side == 0)
		wall_x = game->camera.position.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = game->camera.position.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	// Convertir en coordonnée x de la texture
	tex_x = (int)(wall_x * texture->width);
	if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1
			&& ray->dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	// Calculer la coordonnée y de la texture
	tex_y = (int)((y - ray->draw_start) * texture->height / (ray->draw_end
				- ray->draw_start));
	// Récupérer la couleur du pixel de la texture
	color = ft_get_texture_color(texture, tex_x, tex_y);
	// Appliquer la couleur au pixel
	ft_put_pixel(game, x, y, color);
}

t_texture	*ft_select_texture(t_bag *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (&game->ea_texture);
		return (&game->we_texture);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->so_texture);
		return (&game->no_texture);
	}
}

int	ft_get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;
	int		color;

	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0);
	pixel = texture->addr + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}
