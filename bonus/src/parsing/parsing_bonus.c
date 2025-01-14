/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:12:16 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/10 23:12:53 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	ft_struct_map_init(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->map.fullmap = NULL;
	game->map.no_texture = NULL;
	game->map.so_texture = NULL;
	game->map.we_texture = NULL;
	game->map.ea_texture = NULL;
	game->map.door_texture = NULL;
	game->map.wallsmiley1_texture = NULL;
	game->map.wallsmiley2_texture = NULL;
	game->map.doors = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.is_map_valid = 0;
	game->map.all_info = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = '\0';
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
	game->map.nb_doors = 0;
	game->animation.frame_count = 0;
	game->animation.current_frame = 0;
	game->animation.last_update = 0;
	ft_memset(&game->textures, 0, sizeof(t_textures));
}

void	ft_get_width_height(t_game *game)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	if (game->map.is_map_valid == 1)
		return ;
	while (game->map.fullmap[i])
	{
		j = 0;
		len = ft_strlen(game->map.fullmap[i]);
		if ((size_t)game->map.width < len)
			game->map.width = (int)len;
		i++;
	}
	game->map.height = i;
}

void	ft_parsing(int argc, char **argv, t_game *game)
{
	ft_struct_map_init(game);
	ft_arg_verif(argc, argv, game);
	if (game->map.is_map_valid == 1)
		ft_error_handling(game, NULL);
	ft_map_init(game, argv[1], 0);
	if (game->map.is_map_valid == 1)
		ft_error_handling(game, NULL);
	ft_map_check(game);
	if (game->map.is_map_valid == 1)
		ft_error_handling(game, NULL);
	ft_get_width_height(game);
	if (game->map.is_map_valid == 1)
		ft_error_handling(game, NULL);
}

int	ft_check_texture_prefix(char *buff)
{
	return (!ft_strncmp(buff, "NO ", 3) || !ft_strncmp(buff, "SO ", 3)
		|| !ft_strncmp(buff, "WE ", 3) || !ft_strncmp(buff, "EA ", 3)
		|| !ft_strncmp(buff, "F ", 2) || !ft_strncmp(buff, "C ", 2)
		|| !ft_strncmp(buff, "D ", 2) || !ft_strncmp(buff, "SM1 ", 4)
		|| !ft_strncmp(buff, "SM2 ", 4) || !ft_strncmp(buff, "WIN1 ", 5)
		|| !ft_strncmp(buff, "WIN2 ", 5) || !ft_strncmp(buff, "WIN3 ", 5)
		|| !ft_strncmp(buff, "WIN4 ", 5) || !ft_strncmp(buff, "WIN5 ", 5)
		|| !ft_strncmp(buff, "WIN6 ", 5) || !ft_strncmp(buff, "WIN7 ", 5)
		|| !ft_strncmp(buff, "WIN8 ", 5) || !ft_strncmp(buff, "WIN9 ", 5));
}
// Je check chaque ligne si le premier et dernier caractère est un 1
// Si je croise un espace je regarde si il est
// Je check chaque 0 si il est entouré de soit un 0 ou un 1
// Je check chaque espace si il est entouré de soit un 1 ou un autre espace
// Défauts du parsing :
//	- Si la première ou derniére ligne a des 0 qui dépassent alors la map est
//		alors que la map est techniquement jouable.
