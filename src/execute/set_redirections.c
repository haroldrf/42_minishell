/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:29:29 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 10:48:45 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	set_redir_in(char *file);
static int	set_redir_out(char *file);
static int	set_redir_append(char *file);

int	set_redirections(t_xnode *node)
{
	int	i;

	i = -1;
	while (node->redir[++i])
	{
		if (node->redir[i]->redir_type == REDIR_IN
			&& set_redir_in(node->redir[i]->file))
			return (1);
		if (node->redir[i]->redir_type == REDIR_OUT
			&& set_redir_out(node->redir[i]->file))
			return (1);
		if (node->redir[i]->redir_type == REDIR_APPEND
			&& set_redir_append(node->redir[i]->file))
			return (1);
		if (node->redir[i]->redir_type == REDIR_HEREDOC
			&& set_redir_in("heredoc.tmp"))
			return (1);
	}
	return (0);
}

static int	set_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error: %s: %s\n", file, strerror(errno));
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

static int	set_redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("Error: %s: %s\n", file, strerror(errno));
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

static int	set_redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_printf("Error: %s: %s\n", file, strerror(errno));
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}
