/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:26:28 by fdaumas           #+#    #+#             */
/*   Updated: 2021/11/29 03:02:55 by fdaumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <libc.h>

size_t	ft_strlen(char *str, char c)
{
	int	index;

	index = 0 ;
	while (str[index] != c)
		index++;
	return (index);
}

char	*ft_strchr(char *s, int c)
{
	size_t	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == (char)c)
			return (&((char *)s)[index]);
		index++;
	}
	if (c == '\0')
		return (&((char *)s)[index]);
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	int		index;
	char	*dup;

	index = 0;
	while (s1[index])
		index++;
	dup = malloc(sizeof(char) * (index + 1));
	if (dup == NULL)
		return (NULL);
	index = 0;
	while (s1[index])
	{
		dup[index] = s1[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	index;
	char	*ns;

	if (!s)
		return (0);
	index = 0;
	while (s[start + index])
		index++;
	if (index < len)
		len = index;
	ns = malloc(sizeof(char) * len + 1);
	if (!ns)
		return (NULL);
	index = 0;
	if (start > ft_strlen(s, '\0'))
	{
		ns[0] = '\0';
		return (ns);
	}
	while (index < len && s[start])
		ns[index++] = s[start++];
	ns[index] = '\0';
	return (ns);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	index;
	size_t	len;

	len = 0;
	index = 0;
	if (dstsize > 0)
	{
		while (src[index] && (index < dstsize - 1))
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	while (src[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	index;
	char	*ns;

	if (!s1 || !s2)
		return (0);
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

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*tmp_before_fun;
	char		*new;
	int			verif;

	if (!tmp)
	{
		tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
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

int	main(void)
{
	int		fd;
	char	*test;
	char	*lol;
	char	*lal;
	char	*last;
	char	*try_wihtout;

	fd = open("./test_void", O_RDONLY);
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
}
