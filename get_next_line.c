/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:15:31 by rbestman          #+#    #+#             */
/*   Updated: 2025/01/03 17:38:13 by rbestman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_buf(char *big_buf)
{
	char	*temp_buf;
	size_t len;

	if (!big_buf)
		return (NULL);
	len = 0;
	while (big_buf[len] && big_buf[len] != '\n')
		len++;
	temp_buf = ft_substr(big_buf, len + 1, ft_strlen(big_buf));
	free(big_buf);
	return (temp_buf);
}
	
static char	*append_buffers(char *small_buf, char *big_buf)
{
	char	*temp_buf;

	temp_buf = ft_strjoin(big_buf, small_buf);
	free(big_buf);
	return (temp_buf);
}

static char	*get_line(char *big_buf)
{
	size_t	len;
	char	*line;

	len = 0;
	while (big_buf[len] && big_buf[len] != '\n')
		len++;
	line = ft_substr(big_buf, 0, len);
	return (line);
}

static char	*read_into_buffer(char	*big_buf, int fd)
{
	char	*small_buf;
	int	bytes_read;

	small_buf = malloc(BUFFER_SIZE + 1);
	if (!small_buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, small_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(small_buf), NULL);
		small_buf[bytes_read] = '\0';
		big_buf = append_buffers(small_buf, big_buf);
		if (ft_strchr(big_buf, '\n'))
			break;
	}
	free(small_buf);
	if (bytes_read == 0 && (!big_buf || *big_buf == '\0'))
		return (NULL);
	return (big_buf);
}

char	*get_next_line(int fd)
{
	static char	*big_buf;
	char	*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!big_buf)
		big_buf = ft_strdup("");
	if (!ft_strchr(big_buf, '\n'))
		big_buf = read_into_buffer(big_buf, fd);
	if (!big_buf)
		return (free(big_buf), NULL);
	line = get_line(big_buf);
	big_buf = update_buf(big_buf);
	return (line);
}
