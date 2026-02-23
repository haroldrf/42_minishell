/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:17:39 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/15 17:58:42 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int			process_single_builtin(t_xnode *node, t_shell *ms);
static int			process_pipes(t_xnode *node, t_shell *ms, int last_fd_r);

void	execute(t_shell *ms)
{
	int	status;

	if (ms->last_exit_code != NO_ERROR)
		return ;
	set_signals_to_ignore();
	if (ms->cmd_tree)
	{
		if (!ms->cmd_tree->next && is_builtin(ms->cmd_tree))
			status = process_single_builtin(ms->cmd_tree, ms);
		else
			status = process_pipes(ms->cmd_tree, ms, 0);
		ms->last_exit_code = get_exit_code(status);
		cleanup_cmd_tree(&ms->cmd_tree);
	}
}

static int	process_single_builtin(t_xnode *node, t_shell *ms)
{
	int	fd_backup[2];
	int	status;

	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	if (set_redirections(node))
	{
		cleanup_cmd_tree(&ms->cmd_tree);
		status = 1 << 8;
	}
	else
		status = exec_builtin(node, ms) << 8;
	dup2(fd_backup[0], 0);
	dup2(fd_backup[1], 1);
	close(fd_backup[0]);
	close(fd_backup[1]);
	return (status);
}

static int	process_pipes(t_xnode *node, t_shell *ms, int last_fd_r)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	int		dummy;

	if (pipe(fd) == -1)
		perror("pipe creation");
	pid = fork();
	if (pid == -1)
		perror("fork in pipes");
	else if (pid == 0)
		return (execute_child(node, ms, last_fd_r, fd));
	close(fd[1]);
	if (last_fd_r != 0)
		close(last_fd_r);
	last_fd_r = fd[0];
	if (node->next)
	{
		status = process_pipes(node->next, ms, last_fd_r);
		waitpid(pid, &dummy, 0);
		return (status);
	}
	waitpid(pid, &status, 0);
	close(last_fd_r);
	return (status);
}

int	get_exit_code(int status)
{
	int	exit_code;

	if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	else
		exit_code = WEXITSTATUS(status);
	if (exit_code == 131)
		printf("Quit (core dumped)\n");
	if (exit_code == 130)
		printf("\n");
	return (exit_code % 256);
}
