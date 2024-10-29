/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:04:14 by dloisel           #+#    #+#             */
/*   Updated: 2024/10/29 16:07:41 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_arg_verif(int argc, char **argv, t_bag *game)
{
	char	*format;
	int		len;

	format = ".cub";
	if (argc != 2)
	{
		if (argc > 2)
			ft_error_map("Only 1 argument please.", game);
		else
			ft_error_map("There must be at least 1 argument.", game);
		return ;
	}
	len = ft_strlen(argv[1]);
	if (len < 4)
	{
		ft_error_map("The map file must be in .cub format.", game);
		return ;
	}
	if (ft_strcmp(argv[1] + len - 4, format) != 0)
	{
		ft_error_map("The map file must be in .cub format.", game);
		return ;
	}
}
