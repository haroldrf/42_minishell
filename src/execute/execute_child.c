/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:17:30 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/16 10:48:11 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	set_pipe_child(t_xnode *node, int fd[2], int last_fd_r);
static void	exec_builtin_in_child(t_xnode *node, t_shell *ms);

int	execute_child(t_xnode *node, t_shell *ms, int last_fd_r, int fd[2])
{
	char		*cmd;

	set_signals_to_default();
	set_pipe_child(node, fd, last_fd_r);
	if (set_redirections(node))
	{
		cleanup_shell(ms);
		exit(1);
	}
	if (is_builtin(node))
		exec_builtin_in_child(node, ms);
	cmd = get_cmd_path(node);
	if (!cmd || access(cmd, F_OK))
	{
		if (!cmd)
			ft_printf("Error: %s: command not found\n", node->argv[0]);
		else
			ft_printf("Error: %s: %s\n", cmd, strerror(errno));
		cleanup_shell(ms);
		exit(127);
	}
	execve(cmd, node->argv, ms->env);
	ft_printf("Error: %s: %s\n", cmd, strerror(errno));
	cleanup_shell(ms);
	exit(126);
}

static void	set_pipe_child(t_xnode *node, int fd[2], int last_fd_r)
{
	dup2(last_fd_r, 0);
	if (node->next)
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (last_fd_r != 0)
		close(last_fd_r);
}

static void	exec_builtin_in_child(t_xnode *node, t_shell *ms)
{
	int	status;

	status = exec_builtin(node, ms);
	cleanup_shell(ms);
	exit(status);
}
