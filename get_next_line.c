/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:26:28 by fdaumas           #+#    #+#             */
/*   Updated: 2022/05/26 17:56:18 by fdaumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	index;
	char	*ns;

	index = 0;
	if (s1 == NULL)
	{
		ns = ft_strdup(s2);
		return (ns);
	}
	ns = malloc(sizeof(char) * (ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1));
	if (!ns)
		return (NULL);
	if (ft_strlen(s1, '\0') + ft_strlen(s2, '\0') == 0)
		ns[0] = '\0';
	else
	{
		ft_strlcpy(ns, s1, ft_strlen(s1, '\0') + 1);
		ft_strlcpy(&ns[ft_strlen(s1, '\0')], s2, ft_strlen(s2, '\0') + 1);
		free(s1);
	}
	return (ns);
}

char	*a_line(char *line, char c)
{
	char	*a_line;

	a_line = malloc(sizeof(char) * ft_strlen(line, c) + 2);
	if (!a_line)
		return (NULL);
	ft_strlcpy(a_line, line, ft_strlen(line, c) + 2);
	free(line);
	return (a_line);
}

char	*start(char *before)
{
	char	*save;

	save = ft_strdup(before);
	if (before)
		free(before);
	return (save);
}

char	*read_buf(int fd, int verif, char *buff, char *save)
{
	while (verif != 0 && !ft_strchr(save, '\n'))
	{
		verif = read(fd, buff, BUFFER_SIZE);
		if (verif <= 0)
			break ;
		buff[verif] = '\0';
		save = ft_strjoin_gnl(save, buff);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*before = NULL;
	static char	buff[BUFFER_SIZE + 1];
	char		*save;
	int			verif;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, buff, 0) < 0)
		return (NULL);
	save = start(before);
	verif = 1;
	save = read_buf(fd, verif, buff, save);
	if (ft_strlen(save, '\0') == 0 || save == NULL)
	{
		free(save);
		return (NULL);
	}
	before = ft_substr(save, ft_strlen(save, '\n')
			+ 1, ft_strlen(save, '\0') - ft_strlen(save, '\n'));
	return (a_line(save, '\n'));
}
