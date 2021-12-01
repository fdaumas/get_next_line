/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:26:28 by fdaumas           #+#    #+#             */
/*   Updated: 2021/12/01 15:08:36 by fdaumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
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
	ft_strlcpy(a_line, line, ft_strlen(line, c) + 2);
	free(line);
	return (a_line);
}

char	*start(char *before)
{
	char	*save;

	save = ft_strdup(before);
	free(before);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*before = NULL;
	char		buff[BUFFER_SIZE + 1];
	char		*save;
	int			verif;

	if (read(fd, buff, 0) < 0)
		return (NULL);
	save = start(before);
	verif = 1;
	while (verif != 0 && !ft_strchr(save, '\n'))
	{
		verif = read(fd, buff, BUFFER_SIZE);
		if (verif <= 0)
			break ;
		buff[verif] = '\0';
		save = ft_strjoin(save, buff);
	}
	if (ft_strlen(save, '\0') == 0 || save == NULL)
	{
		free(save);
		return (NULL);
	}
	before = ft_substr(save, ft_strlen(save, '\n')
			+ 1, ft_strlen(save, '\0') - ft_strlen(save, '\n'));
	return (a_line(save, '\n'));
}
/*
int	main(void)
{
	int		fd;
	char	*test;
	char	*lol;
	char	*lal;
	char	*last;
	char	*try_wihtout;

	fd = open("./test", O_RDONLY);
	test = get_next_line(fd);
	printf("final first line = %s\n", test);
	free(test);
	lol = get_next_line(fd);
	printf("final second line = %s\n", lol);
	free(lol);
	lal = get_next_line(fd);
	printf("final third line = %s\n", lal);
	free(lal);
	last = get_next_line(fd);
	printf("final foor line = %s\n", last);
	free(last);
	try_wihtout = get_next_line(fd);
	printf("final five line = %s\n", try_wihtout);
	free(try_wihtout);
	try_wihtout = get_next_line(fd);
	printf("final six line = %s\n", try_wihtout);
	free(try_wihtout);
	try_wihtout = get_next_line(fd);
	printf("final seven line = %s\n", try_wihtout);
	free(try_wihtout);
	try_wihtout = get_next_line(fd);
	printf("final eight line = %s\n", try_wihtout);
	free(try_wihtout);
}
*/
