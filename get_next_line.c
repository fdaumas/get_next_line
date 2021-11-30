/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:26:28 by fdaumas           #+#    #+#             */
/*   Updated: 2021/11/30 19:23:21 by fdaumas          ###   ########.fr       */
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

char	*a_line(char *line)
{
	char	*a_line;

	a_line = malloc(sizeof(char) * ft_strlen(line, '\n') + 2);
	ft_strlcpy(a_line, line, ft_strlen(line, '\n') + 2);
	free(line);
	return (a_line);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		buff[BUFFER_SIZE + 1];
	char		*line;
	int			verif;

	line = ft_strdup(save);
	verif = 1;
	while (verif > 0)
	{
		verif = read(fd, buff, BUFFER_SIZE);
		if (verif <= 0)
			break ;
		buff[verif] = '\0';
		line = ft_strjoin(line, buff);
	}
	if (line)
		save = ft_substr(line, ft_strlen(line, '\n') + 1,
				ft_strlen(line, '\0') - ft_strlen(line, '\n') + 2);
	if (ft_strlen(save, '\0') == 0 && ft_strlen(line, '\0') == 0)
	{
		free(save);
		free(line);
		return (NULL);
	}
	return (a_line(line));
}

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
