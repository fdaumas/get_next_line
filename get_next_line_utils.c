/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 09:36:24 by fdaumas           #+#    #+#             */
/*   Updated: 2021/12/01 14:50:02 by fdaumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str, char c)
{
	int	index;

	index = 0 ;
	while (str[index] != c && str[index])
		index++;
	return (index);
}

char	*ft_strchr(char *s, int c)
{
	size_t	index;

	if (s == NULL || ft_strlen(s, '\0') == 0)
		return (NULL);
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

	if (s1 == NULL)
	{
		dup = malloc(sizeof(char));
		dup[0] = '\0';
		return (dup);
	}
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
