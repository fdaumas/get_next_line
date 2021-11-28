/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaumas <fdaumas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:06:55 by fdaumas           #+#    #+#             */
/*   Updated: 2021/11/28 15:39:53 by fdaumas          ###   ########.fr       */
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
