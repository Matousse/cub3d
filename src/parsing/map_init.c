/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:32:33 by dloisel           #+#    #+#             */
/*   Updated: 2024/12/12 07:17:40 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_extract_map(t_game *game, char *buff, int j, char **temp)
{
	static int	i;

	j = 0;
	if (buff[0] == '\n' && game->map.fullmap == NULL)
		return ;
	temp = game->map.fullmap;
	game->map.fullmap = malloc(sizeof(char *) * (i + 2));
	if (!game->map.fullmap)
		ft_error_map("Allocation error.", game);
	ft_copy_previous_map(game->map.fullmap, temp, i);
	game->map.fullmap[i] = malloc(sizeof(char) * (ft_strlen(buff) + 1));
	if (!game->map.fullmap[i])
		return (free(game->map.fullmap), \
		(void)ft_error_map("Allocation error.", game));
	j = 0;
	while (buff[j] && buff[j] != '\n')
	{
		game->map.fullmap[i][j] = buff[j];
		j++;
	}
	game->map.fullmap[i][j] = '\0';
	game->map.fullmap[i + 1] = NULL;
	i++;
	if (temp)
		free(temp);
}

char	*ft_extract_line_info(char *buff, t_game *game)
{
	int		i;
	int		j;
	int		k;
	char	*info;

	i = 0;
	k = 0;
	game->map.all_info++;
	while (buff[i] == 'N' || buff[i] == 'S' || buff[i] == 'W' || buff[i] == 'E'
		|| buff[i] == 'A' || buff[i] == 'O' || buff[i] == ' ')
		i++;
	j = i;
	while (buff[i] != ' ' && buff[i] != '\n' && buff[i] != '\0')
		i++;
	info = malloc(sizeof(char) * ((i - j) + 1));
	if (!info)
		return (ft_error_map("Allocation error.", game), NULL);
	while (j < i)
	{
		info[k] = buff[j];
		k++;
		j++;
	}
	info[k] = '\0';
	return (info);
}

int	ft_extract_color(char *buff, t_game *game)
{
	int	r;
	int	g;
	int	b;

	game->map.all_info++;
	while (*buff == 'F' || *buff == 'C' || *buff == ' ')
		buff++;
	r = ft_atoi(buff);
	while (*buff && *buff != ',')
		buff++;
	buff++;
	g = ft_atoi(buff);
	while (*buff && *buff != ',')
		buff++;
	buff++;
	b = ft_atoi(buff);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_error_map("RGB values are incorrect.", game), 0);
	return (ft_rgb_to_int(r, g, b));
}

void	ft_extract_info(t_game *game, char *buff)
{
	while (*buff == ' ' || *buff == '\t')
		buff++;
	if (!ft_strncmp(buff, "NO ", 3))
		game->map.no_texture = ft_extract_line_info(buff, game);
	else if (!ft_strncmp(buff, "SO ", 3))
		game->map.so_texture = ft_extract_line_info(buff, game);
	else if (!ft_strncmp(buff, "WE ", 3))
		game->map.we_texture = ft_extract_line_info(buff, game);
	else if (!ft_strncmp(buff, "EA ", 3))
		game->map.ea_texture = ft_extract_line_info(buff, game);
	else if (!ft_strncmp(buff, "F ", 2))
		game->map.floor_color = ft_extract_color(buff, game);
	else if (!ft_strncmp(buff, "C ", 2))
		game->map.ceiling_color = ft_extract_color(buff, game);
}

void	ft_map_init(t_game *game, char *argv, int fd)
{
	char	*buff;

	if (game->map.is_map_valid == 1)
		return ;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error_map("The map couldn't be opened.", game);
	while (1)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		if (!ft_is_map_line(buff) && game->map.all_info < 6)
			ft_extract_info(game, buff);
		else
			ft_extract_map(game, buff, 0, NULL);
		free(buff);
	}
	if (game->map.all_info < 6)
		ft_error_map("Missing elements in .cub file (NO, SO, WE, EA, F, C).",
			game);
	close(fd);
}
