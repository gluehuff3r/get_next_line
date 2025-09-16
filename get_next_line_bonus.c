/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:11:29 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/16 18:32:07 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*trim(char *stash)
{
	char	*newstash;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	newstash = ft_strdup(stash + i);
	if (!newstash)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (newstash);
}

static char	*polish(char *stash)
{
	int		i;
	char	*newline;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	newline = malloc(i + 2);
	if (!newline)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		newline[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		newline[i++] = '\n';
	newline[i] = '\0';
	return (newline);
}

static char	*join_and_free(char *stash, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(stash, buf);
	if (!tmp)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (tmp);
}

static char	*read_into_stash(int fd, char *stash)
{
	char	*buf;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (stashfree(stash));
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		stash = join_and_free(stash, buf);
		if (!stash)
			break ;
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	if (!stash[fd])
		return (NULL);
	stash[fd] = read_into_stash(fd, stash[fd]);
	if (!stash[fd] || *stash[fd] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = polish(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = trim(stash[fd]);
	return (line);
}
