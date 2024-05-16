/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschneid <bschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:01:52 by bschneid          #+#    #+#             */
/*   Updated: 2024/05/10 19:16:54 by bschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_llist
{
	char			*text;
	struct s_llist	*next;
}	t_llist;

typedef struct s_fd_head
{
	int					fd;
	struct s_fd_head	*next;
	t_llist				*begin;
}	t_fd_head;

char	*get_next_line(int fd);
void	*ft_calloc(size_t num, size_t size);
char	has_newline(char *line);
void	refactor_line(char *text);
ssize_t	len_toend(char *element);
void	copy_to_out(char *out, t_llist *segment);

#endif
