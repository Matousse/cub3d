/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:32:33 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 00:17:10 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	ft_extract_map(t_game *game, char *buff, char **temp)
{
	static int		i;
	int				len;

	if (buff[0] == '\n' && game->map.fullmap == NULL)
		return ;
	temp = game->map.fullmap;
	game->map.fullmap = malloc(sizeof(char *) * (i + 2));
	if (!game->map.fullmap)
		ft_error_map("Allocation error.", game);
	ft_copy_previous_map(game->map.fullmap, temp, i);
	len = ft_get_line_length(buff);
	ft_allocate_new_line(game, len, i);
	ft_copy_line(game, buff, len, i);
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
	{
		game->map.all_info++;
		if (!game->map.no_texture)
			game->map.no_texture = ft_extract_line_info(buff, game);
	}
	else if (!ft_strncmp(buff, "SO ", 3))
	{
		game->map.all_info++;
		if (!game->map.so_texture)
			game->map.so_texture = ft_extract_line_info(buff, game);
	}
	else if (!ft_strncmp(buff, "WE ", 3))
	{
		game->map.all_info++;
		if (!game->map.we_texture)
			game->map.we_texture = ft_extract_line_info(buff, game);
	}
	else if (!ft_strncmp(buff, "EA ", 3))
	{
		game->map.all_info++;
		if (!game->map.ea_texture)
			game->map.ea_texture = ft_extract_line_info(buff, game);
	}
	else if (!ft_strncmp(buff, "F ", 2))
	{
		game->map.all_info++;
		if (!game->map.floor_color)
			game->map.floor_color = ft_extract_color(buff, game);
	}
	else if (!ft_strncmp(buff, "C ", 2))
	{
		game->map.all_info++;
		if (!game->map.ceiling_color)
			game->map.ceiling_color = ft_extract_color(buff, game);
	}
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
		if (!ft_is_map_line(buff))
			ft_extract_info(game, buff);
		else
			ft_extract_map(game, buff, NULL);
		free(buff);
	}
	close(fd);
	if (game->map.all_info != 6)
		ft_error_map("Wrong elements in .cub file.", game);
}
