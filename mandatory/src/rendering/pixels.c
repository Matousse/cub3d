/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:59:01 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 18:26:04 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	get_texture_color(t_texture *texture, int x, int y)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	return (texture->data[y * texture->width + x]);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;
	long	offset;

	if (!game || !game->addr || x < 0
		|| x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	offset = y * game->line_length + x * (game->bits_per_pixel / 8);
	if (offset >= WINDOW_WIDTH * WINDOW_HEIGHT * (game->bits_per_pixel / 8))
		return ;
	dst = game->addr + offset;
	*(unsigned int *)dst = color;
}
