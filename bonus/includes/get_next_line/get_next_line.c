/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:11:06 by dloisel           #+#    #+#             */
/*   Updated: 2024/06/05 20:38:49 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_error(char *str, char *str2)
{
	free(str);
	if (!str2)
		return (NULL);
	free(str2);
	return (NULL);
}

char	*extract_line(char *stash)
{
	char	*str;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = stash[i];
		i--;
	}
	return (str);
}

char	*clean_stash(char *stash)
{
	char	*clean_stash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (ft_error(stash, 0));
	clean_stash = malloc(sizeof(char) * (ft_strlen2(stash) - i + 1));
	if (!clean_stash)
		return (ft_error(stash, 0));
	i++;
	while (stash[i])
		clean_stash[j++] = stash[i++];
	clean_stash[j] = '\0';
	free(stash);
	return (clean_stash);
}

char	*add_to_stash(int fd, char *stash)
{
	int		status;
	char	*buff;
	char	*tmp;

	status = 1;
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (ft_error(stash, 0));
	while (status)
	{
		status = read(fd, buff, BUFFER_SIZE);
		if (status == -1)
			return (ft_error(stash, buff));
		buff[status] = '\0';
		tmp = ft_strjoin2(stash, buff);
		free(stash);
		stash = tmp;
		if (!stash)
			return (ft_error(buff, 0));
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	if (!stash)
		return (NULL);
	stash = add_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = 0;
		return (NULL);
	}
	stash = clean_stash(stash);
	return (line);
}
