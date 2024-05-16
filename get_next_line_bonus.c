/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschneid <bschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:00:39 by bschneid          #+#    #+#             */
/*   Updated: 2024/05/16 15:08:08 by bschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Fills a llist to a given head (connected to fd) until read '\n'
char	fill_llist(t_fd_head *head, t_llist **end, ssize_t bytes_read)
{
	if (!head->begin)
		end = &(head->begin);
	else if (has_newline(head->begin->text))
		return (1);
	else
		end = &(head->begin->next);
	while (1)
	{
		*end = (t_llist *)malloc(sizeof(t_llist));
		if (*end == NULL)
			return (0);
		(*end)->next = NULL;
		(*end)->text = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!(*end)->text)
			return (0);
		bytes_read = read(head->fd, (*end)->text, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		if (has_newline((*end)->text) || len_toend((*end)->text) < BUFFER_SIZE)
			return (1);
		end = &((*end)->next);
	}
	return (1);
}

char	*create_line(t_fd_head *head, ssize_t full_len)
{
	t_llist	*end;
	char	*out;
	ssize_t	line_len;

	if (!head->begin || !len_toend(head->begin->text))
		return (0);
	end = head->begin;
	while (end)
	{
		line_len = len_toend(end->text);
		full_len += line_len;
		if (!line_len)
			end = NULL;
		else
			end = end->next;
	}
	out = (char *)malloc((full_len + 1) * sizeof(char));
	if (!out)
		return (0);
	copy_to_out(out, head->begin);
	return (out);
}

void	clean_list(t_fd_head *head, char *out)
{
	t_llist	*element;
	t_llist	*tmp;

	if (!head || !head->begin)
		return ;
	element = head->begin;
	while (element && (!has_newline(element->text) || !out))
	{
		tmp = element->next;
		if (element->text)
			free(element->text);
		free(element);
		element = tmp;
	}
	if (element && out)
		refactor_line(element->text);
	if (element && (!len_toend(element->text) || !out))
	{
		if (element->text)
			free(element->text);
		free(element);
		element = NULL;
	}
	head->begin = element;
}

t_fd_head	**add_or_find_head(t_fd_head **head, int fd)
{
	while (*head)
	{
		if ((*head)->fd == fd)
			return (head);
		head = &((*head)->next);
	}
	(*head) = (t_fd_head *)malloc(sizeof(t_fd_head));
	if (!(*head))
		return (0);
	(*head)->fd = fd;
	(*head)->begin = NULL;
	(*head)->next = NULL;
	return (head);
}

char	*get_next_line(int fd)
{
	static t_fd_head	*head_list;
	t_fd_head			**head;
	t_fd_head			*tmp;
	char				*out;

	out = 0;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (0);
	head = add_or_find_head(&head_list, fd);
	if (head && fill_llist(*head, 0, 0))
		out = create_line(*head, 0);
	if (head)
		clean_list(*head, out);
	if (head && !out)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	return (out);
}