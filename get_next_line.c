/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:19:41 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/13 21:34:47 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "get_next_line.h"

 char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}
char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
char *trim(char * stash)
{
	char *newstash;
	int i = 0;
	while (stash[i] && stash[i] != '\n')
        i++;
	if(!stash[i])
	{
		free(stash);
		return NULL;
	}
	i++;
	newstash = ft_strdup(stash + i);
    free(stash);
	return(newstash);
}
char *polish(char *stash)
{
    int i = 0;
    char *newline;

    if (!stash[0])
        return NULL;
    while (stash[i] && stash[i] != '\n')
        i++;
    newline = malloc(i + 2);
    if (!newline)
        return NULL;
    i = 0;
    while (stash[i] && stash[i] != '\n')
    {
        newline[i] = stash[i];
        i++;
    }
    if (stash[i] == '\n')
        newline[i++] = '\n';
    newline[i] = '\0';
    return newline;
}
char    *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE + 1]; 
    static char        *stash;
    int         bytes_read;
	char  *temp;
	char	*newline;
	
	 if (!stash)
        stash = ft_strdup("");
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
        return (NULL);
    buffer[bytes_read] = '\0';
    temp = ft_strjoin(stash, buffer);
	free(stash);
	stash = temp;
	newline = polish(stash);
	stash = trim(stash);
	return (newline); 
}

#include <stdio.h>
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	(line = get_next_line(fd));
	{
		printf("%s", line);
		free(line); 
	}	
	close(fd);
	return 0;
}