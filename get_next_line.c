/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagomez <vagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:41:47 by vanessa           #+#    #+#             */
/*   Updated: 2025/02/27 19:59:38 by vagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *s, int c)
{
	size_t	i;
	char	target;

	i = 0;
	target = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == target)
			return ((char *)&s[i]);
		i++;
	}
	if (target == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

static char	*read_data(int fd, char *collected_data, char *buffer)
{
	ssize_t	byte;
	char	*tmp_buffer;

	byte = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || buffer == NULL)
		return (NULL);
	while (byte > 0)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
			return (free(collected_data), NULL);
		if (byte == 0)
			break ;
		buffer[byte] = '\0';
		if (collected_data == NULL)
			collected_data = ft_strdup("");
		tmp_buffer = collected_data;
		collected_data = ft_strjoin(tmp_buffer, buffer);
		free(tmp_buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (collected_data);
}

static char	*extract_line(char *buffer)
{
	size_t	i;
	char	*remaining;

	i = 0;
	if (buffer == NULL)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0' || buffer[1] == '\0')
		return (NULL);
	remaining = ft_substr(buffer, i + 1, ft_strlen(buffer) - i);
	if (*remaining == '\0')
	{
		free(remaining);
		remaining = NULL;
	}
	buffer[i + 1] = '\0';
	return (remaining);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*remaining;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(remaining);
		remaining = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	line = read_data(fd, remaining, buffer);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	remaining = extract_line(line);
	return (line);
}
