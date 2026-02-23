/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:12:49 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/16 12:33:12 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	create_heredoc_tmp(t_redir *redir, t_shell *shell);
static void	create_heredoc_tmp_child(t_redir *redir, int fd, t_shell *shell);

// even if the exit status is set to error, we process the heredoc 
// HRF: what does it mean ???
void	heredoc(t_shell *shell)
{
	t_xnode	*current;
	int		i;

	if (shell->last_exit_code > 0)
		return ;
	set_signals_to_ignore();
	current = shell->cmd_tree;
	while (current)
	{
		i = 0;
		while (current->redir[i])
		{
			if (current->redir[i]->redir_type == REDIR_HEREDOC
				&& create_heredoc_tmp(current->redir[i], shell))
			{
				cleanup_cmd_tree(&shell->cmd_tree);
				return ;
			}
			i++;
		}
		current = current->next;
	}
}

static int	create_heredoc_tmp(t_redir *redir, t_shell *shell)
{
	int		pid;
	int		status;
	int		fd;

	fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("Error: %s: %s\n", "heredoc.tmp", strerror(errno));
		return (1);
	}
	pid = fork();
	if (pid == -1)
		perror("fork in heredoc_parsing");
	if (pid == 0)
		create_heredoc_tmp_child(redir, fd, shell);
	waitpid(pid, &status, 0);
	close(fd);
	shell->last_exit_code = get_exit_code(status);
	return (shell->last_exit_code);
}

static void	create_heredoc_tmp_child(t_redir *redir, int fd, t_shell *shell)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	while (line && ft_strcmp(line, redir->heredoc_dlm))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (!line)
		ft_printf("Warning : here-doc terminated with end-of-file.\n");
	free(line);
	close(fd);
	cleanup_shell(shell);
	exit(0);
}
