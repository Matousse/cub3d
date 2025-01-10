/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:15:45 by dloisel           #+#    #+#             */
/*   Updated: 2024/06/06 14:00:02 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_error(char *str, char *str2);
char	*clean_stash(char *stash);
char	*extract_line(char *stash);
char	*add_to_stash(int fd, char *stash);
char	*get_next_line(int fd);
size_t	ft_strlen2(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin2(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);

#endif