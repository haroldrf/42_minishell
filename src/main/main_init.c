/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:10:02 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/10 14:00:37 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			init_shell(t_shell *shell, char **envp);
static int	init_env(char ***env, char **envp);
static int	fill_up_env(char **env, char **envp, int n);

int	init_shell(t_shell *shell, char **envp)
{
	shell->cmd_tree = NULL;
	shell->state = NULL;
	shell->last_exit_code = 0;
	if (init_env(&shell->env, envp) != NO_ERROR)
		return (shell->last_exit_code = GENERAL_ERROR);
	return (NO_ERROR);
}

static int	init_env(char ***env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	*env = malloc(sizeof(char *) * (i + 1));
	if (!*env)
		return (GENERAL_ERROR);
	if (fill_up_env(*env, envp, i) != NO_ERROR)
	{
		free(*env);
		return (GENERAL_ERROR);
	}
	return (NO_ERROR);
}

static int	fill_up_env(char **env, char **envp, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (--i >= 0)
				free(env[i]);
			return (GENERAL_ERROR);
		}
		i++;
	}
	env[n] = NULL;
	return (NO_ERROR);
}
