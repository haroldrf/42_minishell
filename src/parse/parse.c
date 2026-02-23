/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:34:06 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/16 12:45:48 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			parse(char *input, t_shell *shell);
static int	init_state(t_shell *shell, char *input, int max_tok);
void		reset_shell_state(t_shell *shell);

/* initialise STATE, tokenize*/
int	parse(char *input, t_shell *shell)
{
	int	exit_token;
	int	max_token;

	max_token = 50;
	init_state(shell, input, max_token);
	exit_token = tokenize(shell, max_token);
	if (exit_token == 0)
		expand(shell);
	delete_empty(shell);
	retoken(shell);
	combine(shell);
	grammar(shell);
	command(shell);
	heredoc(shell);
	if (shell->last_exit_code == MEMORY_ALLOCATION_ERROR)
	{
		ft_printf("Error: memory allocation failure. Exiting minishell.\n");
		cleanup_shell(shell);
		exit(GENERAL_ERROR);
	}
	cleanup_state(shell->state);
	shell->state = NULL;
	return (shell->last_exit_code);
}

static int	init_state(t_shell *shell, char *input, int max_tok)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	if (!state)
		return (shell->last_exit_code = MEMORY_ALLOCATION_ERROR);
	state->input_string = NULL;
	if (*input)
		state->input_string = ft_strdup(input);
	if (*input && !state->input_string)
	{
		free(state);
		return (shell->last_exit_code = MEMORY_ALLOCATION_ERROR);
	}
	state->token_count = 0;
	state->tokens = malloc(sizeof(t_token *) * (max_tok));
	if (!state->tokens)
	{
		free(state->input_string);
		free(state);
		return (shell->last_exit_code = MEMORY_ALLOCATION_ERROR);
	}
	shell->state = state;
	return (NO_ERROR);
}
