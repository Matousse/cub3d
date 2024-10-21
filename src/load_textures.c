/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:45:12 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 23:47:03 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_bag *bag, int index, char *path)
{
	t_texture	*tex;

	tex = &bag->textures[index];
	tex->img = mlx_xpm_file_to_image(bag->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		ft_printf("Error when loading a texture\n");
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}
