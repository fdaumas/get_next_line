/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:26:28 by fdaumas           #+#    #+#             */
/*   Updated: 2021/11/29 14:51:31 by fdaumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	index;
	char	*ns;

	index = 0;
	ns = malloc(sizeof(char) * (ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1));
	if (!ns)
		return (NULL);
	if (ft_strlen(s1, '\0') + ft_strlen(s2, '\0') == 0)
		ns[0] = '\0';
	while (s1[index])
	{
		ns[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index])
	{
		ns[index + ft_strlen(s1, '\0')] = s2[index];
		index++;
	}
	ns[index + ft_strlen(s1, '\0')] = '\0';
	return (ns);
}

char	*new_str(char *new, int len)
{
	char	tmp[len];
	char	*return_value;

	ft_strlcpy(tmp, new, ft_strlen(new, '\n') + 2);
	free(new);
	return_value = ft_strdup(tmp);
	return (return_value);
}

char	*get_next_line(int fd)
{
	static char	*tmp = NULL;
	char		*tmp_before_fun;
	char		*new;
	int			verif;

	if (!tmp)
	{
		tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!tmp)
			return (NULL);
		verif = read(fd, tmp, BUFFER_SIZE);
		if (verif == 0 || verif == -1)
			return (NULL);
		tmp[verif] = '\0';
	}
	new = ft_strdup(tmp);
	while (!ft_strchr(tmp, '\n') || !ft_strchr(tmp, '\0'))
	{
		tmp_before_fun = malloc(sizeof(char) * BUFFER_SIZE + 1);
		verif = read(fd, tmp_before_fun, BUFFER_SIZE);
		if (verif == 0 || verif == -1)
		{
			free(new);
			free(tmp_before_fun);
			return (NULL);
		}
		tmp_before_fun[verif] = '\0';
		free(new);
		new = ft_strjoin(tmp, tmp_before_fun);
		free(tmp_before_fun);
		free(tmp);
		tmp = ft_strdup(new);
	}
	free(tmp);
	tmp = ft_substr(new, ft_strlen(new, '\n')
			+ 1, ft_strlen(new, '\0') - ft_strlen(new, '\n'));
	tmp_before_fun = malloc(sizeof(char) * ft_strlen(new, '\n') + 2);
	ft_strlcpy(tmp_before_fun, new, ft_strlen(new, '\n') + 2);
	free(new);
	if (!tmp_before_fun)
	{
		free(tmp_before_fun);
		return (NULL);
	}
	return (tmp_before_fun);
}

//int	main(void)
//{
//	int		fd;
//	char	*test;
//	char	*lol;
//	char	*lal;
//	char	*last;
//	char	*try_wihtout;
//
//	fd = open("./test", O_RDONLY);
//	test = get_next_line(fd);
//	printf("final first line = %s\n", test);
//	free(test);
//	lol = get_next_line(fd);
//	printf("final second line = %s\n", lol);
//	free(lol);
//	lal = get_next_line(fd);
//	printf("final third line = %s\n", lal);
//	free(lal);
//	last = get_next_line(fd);
//	printf("final foor line = %s\n", last);
//	free(last);
//	try_wihtout = get_next_line(fd);
//	printf("final five line = %s\n", try_wihtout);
//	free(try_wihtout);
//}
