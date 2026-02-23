/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:39:08 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/16 12:46:46 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			main(int argc, char *argv[], char *envp[]);
static int	loop(t_shell *shell);
static bool	ft_isonlyspace(char *string);

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;
	int		exit_code;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (GENERAL_ERROR);
	exit_code = init_shell(shell, envp);
	if (exit_code != NO_ERROR)
	{
		free(shell);
		return (exit_code);
	}
	setup_signals_interactive();
	disable_ctrl_backslash_echo();
	exit_code = loop(shell);
	cleanup_shell(shell);
	enable_ctrl_backslash_echo();
	printf("Exit\n");
	return (exit_code);
}

static int	loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		disable_ctrl_backslash_echo();
		setup_signals_interactive();
		input = readline("\033[1;34mminishell>\033[0m ");
		if (!input)
			break ;
		if (*input && !ft_isonlyspace(input))
		{
			add_history(input);
			parse(input, shell);
			execute(shell);
			if (shell->last_exit_code == NO_TOKEN)
				shell->last_exit_code = NO_ERROR;
		}
		free(input);
	}
	rl_clear_history();
	return (shell->last_exit_code);
}

static bool	ft_isonlyspace(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_isspace(string[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
