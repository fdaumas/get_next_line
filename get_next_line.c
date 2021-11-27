/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:26:28 by fdaumas           #+#    #+#             */
/*   Updated: 2021/11/27 20:20:27 by fdaumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <libc.h>

size_t	ft_strlen(char *str)
{
	int	index;

	index = 0 ;
	while (str[index] != '\0' && str[index] != '\n')
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

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	index;
	size_t	len_dest;
	size_t	len_src;

	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	index = 0;
	if (dstsize < len_dest || dstsize == 0)
		return (len_src + dstsize);
	while (src[index] != '\0' && index + len_dest < dstsize - 1)
	{
		dst[len_dest + index] = src[index];
		index++;
	}
	dst[len_dest + index] = '\0';
	return (len_dest + len_src);
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
	ns = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ns)
		return (NULL);
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
		ns[0] = '\0';
	while (s1[index])
	{
		ns[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index])
	{
		ns[index + ft_strlen(s1)] = s2[index];
		index++;
	}
	ns[index + ft_strlen(s1)] = '\0';
	return (ns);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*tmp_before_fun;
	char		*new;
	int			verif;

	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	tmp_before_fun = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
	{
		verif = read(fd, tmp, BUFFER_SIZE);
		printf("%s\n", tmp);
		if (verif == 0 || verif == -1)
			return (NULL);
	}
	new = ft_strdup(tmp);
	while (!ft_strchr(tmp, '\n'))
	{
		verif = read(fd, tmp_before_fun, BUFFER_SIZE);
		if (verif == 0 || verif == -1)
			return (NULL);
		new = ft_strjoin(tmp, tmp_before_fun);
		free(tmp);
		tmp = ft_strdup(new);
		printf("%s\n", new);
	}
	free(tmp);
	free(tmp_before_fun);
/*
** 	tmp = ft_strchr(new, '\n')
** 	len = ft_strlcpy(tmp_before_fun, tmp, len);
** 	tmp = ;
** 	ft_strlcpy(new, tmp_before_fun, ft_strlen(tmp_before_fun));
** 	new = ft_strdup(new);
*/
	return (new);
}

int	main(void)
{
	int	fd;

	fd = open("./test", O_RDONLY);
	printf("%s", get_next_line(fd));
}
