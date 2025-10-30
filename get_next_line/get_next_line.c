/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:45:13 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/30 10:47:25 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_joinfree(char *buffer, char *buff)
{
	char	*result;

	result = ft_strjoin(buffer, buff);
	return (result);
}

char	*ft_get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_get_next(char *buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		return (NULL);
	}
	next = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!next)
		return (NULL);
	i++;
	while (buffer[i])
		next[j++] = buffer[i++];
	next[j] = '\0';
	return (next);
}

char	*read_file(int fd, char *buffer)
{
	char	*dybuffer;
	int		i_re;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	dybuffer = gc_malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!dybuffer)
		return (NULL);
	i_re = 1;
	while (i_re > 0)
	{
		i_re = read(fd, dybuffer, BUFFER_SIZE);
		if (i_re == -1)
		{
			return (NULL);
		}
		dybuffer[i_re] = 0;
		buffer = ft_joinfree(buffer, dybuffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_get_next(buffer);
	if (!buffer)
		buffer = NULL;
	return (line);
}
