/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:19:41 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/15 09:40:25 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim(char *stash)
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
	free(stash);
	return (newstash);
}

char	*polish(char *stash)
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
	free(stash);
	return (tmp);
}

static char	*read_into_stash(int fd, char *stash)
{
	char	*buf;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (stash);
	bytes_read = 1;
	while (bytes_read >= 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		stash = join_and_free(stash, buf);
	}
	if (bytes_read < 0)
	{
		free(buf);
		free(stash);
		return (NULL);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = read_into_stash(fd, stash);
	if (!stash || !stash[0])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = polish(stash);
	stash = trim(stash);
	return (line);
}

// // 2️⃣ Override malloc temporarily
// #define malloc(x) my_malloc(x)

// #include "get_next_line.h"  // include after the macro override

// int main(void)
// {
//     int fd;
//     char *line;

//     fd = open("test.txt", O_RDONLY);
//     if (fd < 0)
//         return (1);

//     line = get_next_line(fd);
//     if (!line)
//         printf("Malloc failed, get_next_line returned NULL safely!\n");

//     close(fd);
//     return (0);
// }

// #include "get_next_line.h"
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line;
// 	int i = 1;
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("Line %d: %s", i, line);
// 		free(line);
// 		i++;
// 	}

// 	close(fd);
// 	return (0);
// }