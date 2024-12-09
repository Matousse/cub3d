/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:54:19 by dmathis           #+#    #+#             */
/*   Updated: 2024/11/08 21:07:37 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_cleanup_textures(t_bag *game)
{
	if (game->no_texture.img)
		mlx_destroy_image(game->mlx, game->no_texture.img);
	if (game->so_texture.img)
		mlx_destroy_image(game->mlx, game->so_texture.img);
	if (game->we_texture.img)
		mlx_destroy_image(game->mlx, game->we_texture.img);
	if (game->ea_texture.img)
		mlx_destroy_image(game->mlx, game->ea_texture.img);
}

// Fonction de cleanup générale à appeler à la fin
void	ft_cleanup(t_bag *game)
{
	ft_cleanup_textures(game);
	if (game->db_buff_img)
		mlx_destroy_image(game->mlx, game->db_buff_img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_free_map(game);
	free(game);
}

int	ft_error_handling(t_bag *game, char *message)
{
	ft_cleanup(game);
	if (message)
	{
		ft_printf(RED "%s\n", "Error");
		ft_printf("%s\n" RESET, message);
	}
	exit(0);
	return (0);
}
