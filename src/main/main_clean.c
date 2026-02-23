/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:46:15 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/15 17:55:32 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cleanup_shell(t_shell *shell);
void	cleanup_env(char **env);
void	cleanup_state(t_state *state);
void	cleanup_tokens(t_state *state);

void	cleanup_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmd_tree)
			cleanup_cmd_tree(&shell->cmd_tree);
		if (shell->state)
			cleanup_state(shell->state);
		if (shell->env)
			cleanup_env(shell->env);
		shell->state = NULL;
		shell->env = NULL;
	}
	free(shell);
}

void	cleanup_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
			free(env[i++]);
		free(env);
	}
}

void	cleanup_state(t_state *state)
{
	if (state)
	{
		cleanup_tokens(state);
		if (state->input_string)
			free(state->input_string);
		state->tokens = NULL;
		state->input_string = NULL;
		free(state);
	}
}

void	cleanup_tokens(t_state *state)
{
	int	i;

	if (state && state->tokens)
	{
		i = 0;
		while (state->tokens[i])
		{
			if (state->tokens[i])
			{
				free(state->tokens[i]->value);
				free(state->tokens[i]);
				state->tokens[i] = NULL;
			}
			i++;
		}
		free(state->tokens);
		state->tokens = NULL;
		state->token_count = 0;
	}
}
