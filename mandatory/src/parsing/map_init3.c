/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:33:46 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 15:34:39 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_number(char *temp, char expected_end)
{
	if (!(*temp >= '0' && *temp <= '9'))
		return (0);
	while (*temp >= '0' && *temp <= '9')
		temp++;
	if (*temp != expected_end)
		return (0);
	return (1);
}

int	check_values_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

int	check_color_values(char *buff, int *r, int *g, int *b)
{
	while (*buff == 'F' || *buff == 'C' || *buff == ' ')
		buff++;
	if (!check_number(buff, ','))
		return (printf("check1\n"), 0);
	*r = ft_atoi(buff);
	while (*buff != ',')
		buff++;
	buff++;
	if (!check_number(buff, ','))
		return (0);
	*g = ft_atoi(buff);
	while (*buff != ',')
		buff++;
	buff++;
	if (!check_number(buff, '\n'))
		return (0);
	*b = ft_atoi(buff);
	return (check_values_range(*r, *g, *b));
}
