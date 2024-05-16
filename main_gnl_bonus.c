/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschneid <bschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:42:42 by bschneid          #+#    #+#             */
/*   Updated: 2024/05/16 15:10:17 by bschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line_bonus.h"

// cc -g main_gnl_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o main_gnl_bonus.out
int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;
	int		lines;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("Couldn't open text1 or text2!");
		return (1);
	}
	lines = 1;
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	while (line1 || line2)
	{
		if (line1)
		{
			printf("%d.Line test1 -> %s", lines, line1);
			free(line1);
		}
		if (line2)
		{
			printf("%d.Line test2 -> %s", lines, line2);
			free(line2);
		}
		printf("\n");
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		lines++;
	}
	return (0);
}
