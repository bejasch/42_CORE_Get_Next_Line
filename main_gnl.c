/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschneid <bschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:42:42 by bschneid          #+#    #+#             */
/*   Updated: 2024/05/16 14:50:59 by bschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

// cc -g main_gnl.c get_next_line.c get_next_line_utils.c -o main_gnl.out
int	main(void)
{
	int		fd;
	char	*line;
	int		lines;

	lines = 1;
	fd = open("test1.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Couldn't open text1!");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%d.Line -> %s", lines++, line);
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	return (0);
}
