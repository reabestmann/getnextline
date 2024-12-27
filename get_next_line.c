/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:15:31 by rbestman          #+#    #+#             */
/*   Updated: 2024/12/27 17:13:54 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

static char	*read_and_store(int fd, char **leftover)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (!ft_strchr(*leftover, '\n') && bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		*leftover = ft_strjoin(*leftover, buffer);
	}
	if (bytes_read < 0)
	{
		free(*leftover);
		return (NULL);
	}
	free(buffer);
	return (*leftover);
}

static char	*get_line(char **leftover)
{
	size_t	i;
	char	*line;
	char	*leftover_new;

	i = 0;
	while ((*leftover)[i] && (*leftover)[i] != '\n')
		i++;
	line = ft_substr(*leftover, 0, i + ((*leftover)[i] == '\n'));
	*leftover_new = ft_strdup(*leftover + i + ((*leftover)[i] == '\n'));
	free(*leftover);
	*leftover = new_leftover;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*leftover;

	leftover = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_and_store(fd, &leftover))
		return (NULL);
	if (!leftover || !*leftover)
		return (NULL);
	return (get_line(&leftover));
}
