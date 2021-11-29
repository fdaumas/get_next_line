/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:06:55 by fdaumas           #+#    #+#             */
/*   Updated: 2021/11/29 13:08:23 by fdaumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static void	fun(void)
{
	static char	*count;

	if (!count)
		count = "lol";
	printf("%s", count);
	count = "super";
	count = "test";
}

int	main(void)
{
	int		fd;
	char	str[BUFFER_SIZE];
	int	verif;

	fd = open("./test", O_RDONLY);
	printf("%i\n", BUFFER_SIZE);
	fun();
	fun();
	fun();
	printf("fd  = %i\n", fd);
	verif = read(fd, str, BUFFER_SIZE);
	if (verif == 0 || verif == -1)
		printf("read not OK");
	else
		str[verif] = '\0';
	printf("%i\n", verif);
	printf("%s", str);
}

//char	*get_next_line(int fd)
{
	static char	*tmp = NULL;
	char		*tmp_before_fun;
	char		*new;
	int			verif;

	if (!tmp)
	{
		tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!tmp)
			return(NULL);
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

//char	*get_next_line(int fd)
{
	static char	*tmp = NULL;
	char		buf[BUFFER_SIZE + 1];
	char		*join;
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
	join = strdup(tmp);
	while (!ft_strchr(tmp, '\n') || !ft_strchr(tmp, '\0'))
	{
		verif = read(fd, buf, BUFFER_SIZE);
		if (verif == 0 || verif == -1)
		{
			free(tmp);
			return (NULL);
		}
		buf[verif] = '\0';
		free(join);
		join = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = ft_strdup(join);
	}
	free(tmp);
	tmp = ft_substr(join, ft_strlen(join, '\n')
			+ 1, ft_strlen(join, '\0') - ft_strlen(join, '\n') + 2);
	new = new_str(join);
	free(join);
	return (new);
}
