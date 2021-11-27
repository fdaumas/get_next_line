/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:06:55 by fdaumas           #+#    #+#             */
/*   Updated: 2021/11/27 15:59:22 by fdaumas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static int	fun(void)
{
	static int	count = 0;

	count++;
	return (count);
}

int	main(void)
{
	int		fd;
	char	str[BUFFER_SIZE];
	int	verif;

	fd = open("./test", O_RDONLY);
	printf("%i\n", BUFFER_SIZE);
	printf("%i\n", fun());
	printf("%i\n", fun());
	printf("%i\n", fun());
	printf("%i\n", fun());
	printf("fd  = %i\n", fd);
	verif = read(fd, str, BUFFER_SIZE);
	if (verif == 0 || verif == -1)
		printf("read not OK");
	else
		str[verif] = '\0';
	printf("%i\n", verif);
	printf("%s", str);
}
