/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 03:32:21 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/13 03:32:21 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "get_next_line.h"

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
char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1]; 
    char        *line;
    int         bytes_read;

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
        return (NULL);
    buffer[bytes_read] = '\0';
    line = ft_strdup(buffer);
	return (line); 
}

#include <stdio.h>
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line); 
	}	
	close(fd);
	return 0;
}