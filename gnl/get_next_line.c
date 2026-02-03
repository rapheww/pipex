/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:07:23 by rchaumei          #+#    #+#             */
/*   Updated: 2026/02/03 23:32:51 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_fill_tmp(char *tmp, char *buf)
{
	char	*old_tmp;

	if (tmp)
	{
		old_tmp = tmp;
		tmp = ft_strjoin(tmp, buf);
		free(buf);
		free(old_tmp);
		buf = NULL;
	}
	else
	{
		tmp = ft_strdup(buf);
		free(buf);
		buf = NULL;
	}
	return (tmp);
}

char	*ft_fill_line(char *tmp)
{
	int		i;
	char	*line;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i += 1;
	line = ft_substr(tmp, 0, i);
	return (line);
}

int	ft_reading(char **tmp, int *read_bytes, int fd)
{
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	*read_bytes = read(fd, buf, BUFFER_SIZE);
	if (*read_bytes < 0)
	{
		free(buf);
		if (*tmp)
		{
			free(*tmp);
			*tmp = NULL;
		}
		return (0);
	}
	buf[*read_bytes] = '\0';
	*tmp = ft_fill_tmp(*tmp, buf);
	return (1);
}

char	*extract_line(char **tmp, char **line)
{
	char	*keep;

	keep = ft_strdup(ft_strchr(*tmp, '\n') + 1);
	*line = ft_fill_line(*tmp);
	free(*tmp);
	*tmp = NULL;
	*tmp = ft_strdup(keep);
	if (!(*tmp))
		return (NULL);
	free(keep);
	keep = NULL;
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	int			read_bytes;
	char		*line;

	read_bytes = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(tmp), NULL);
	while (read_bytes != 0)
	{
		if (tmp && ft_strchr(tmp, '\n') != NULL)
			return (extract_line(&tmp, &line));
		if (ft_reading(&tmp, &read_bytes, fd) == 0)
			return (NULL);
	}
	if (tmp && *tmp)
	{
		line = tmp;
		tmp = NULL;
		return (line);
	}
	free(tmp);
	tmp = NULL;
	return (NULL);
}
