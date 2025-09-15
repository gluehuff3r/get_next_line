/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:19:25 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/13 21:31:00 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42  
#endif

# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

char	*get_next_line(int fd);

// helpers in get_next_line.c
char	*trim(char *stash);
char	*polish(char *stash);
static char *read_into_stash(int fd, char *stash);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
#endif
