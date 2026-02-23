/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:01:28 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/16 10:49:33 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			grammar(t_shell *shell);
static void	remove_type_quotes(t_state *state);
static void	retype_direction_file(t_state *state);
static int	error_redir_p(t_state *state);

/* if operand at the end or pipe at the beginning -> error */
int	grammar(t_shell *sh)
{
	int	exit_code;
	int	n;

	if (sh->last_exit_code != NO_ERROR)
		return (sh->last_exit_code);
	n = sh->state->token_count;
	if (sh->state->tokens[0]->type == 2 || (sh->state->tokens[n - 1]->type > 1 
			&& sh->state->tokens[n - 1]->type < 7))
	{
		ft_printf("Error: parse error near operand.\n");
		return (sh->last_exit_code = SHELL_BUILTIN_ERROR);
	}
	remove_type_quotes(sh->state);
	retype_direction_file(sh->state);
	exit_code = error_redir_p(sh->state);
	sh->last_exit_code = exit_code;
	return (exit_code);
}

/* all quoted types => token words */
static void	remove_type_quotes(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->token_count)
	{
		if (state->tokens[i]->type == TOKEN_DOUBLE_Q 
			|| state->tokens[i]->type == TOKEN_SINGLE_Q)
			state->tokens[i]->type = TOKEN_WORD;
		i++;
	}
}

/* if < > << >> -> correctly mark the associated file / dlm */
static void	retype_direction_file(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->token_count - 1)
	{
		if (state->tokens[i]->type == TOKEN_REDIR_IN
			&& state->tokens[i + 1]->type == TOKEN_WORD)
			state->tokens[i + 1]->type = FILE_REDIR_IN;
		else if (state->tokens[i]->type == TOKEN_REDIR_OUT
			&& state->tokens[i + 1]->type == TOKEN_WORD)
			state->tokens[i + 1]->type = FILE_REDIR_OUT;
		else if (state->tokens[i]->type == TOKEN_APPEND
			&& state->tokens[i + 1]->type == TOKEN_WORD)
			state->tokens[i + 1]->type = FILE_APPEND;
		else if (state->tokens[i]->type == TOKEN_HEREDOC
			&& state->tokens[i + 1]->type == TOKEN_WORD)
			state->tokens[i + 1]->type = HEREDOC_DLM;
		i++;
	}
}

/* < > << >>  without associated file? double pipe? error */
static int	error_redir_p(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->token_count - 1)
	{
		if (((state->tokens[i]->type >= 3 && state->tokens[i]->type <= 6)
				&& (state->tokens[i + 1]->type != state->tokens[i]->type + 6))
			|| (state->tokens[i]->type == TOKEN_PIPE
				&& state->tokens[i + 1]->type == TOKEN_PIPE))
		{
			ft_printf("Error: parse error near operand.\n");
			return (SHELL_BUILTIN_ERROR);
		}
		i++;
	}
	return (NO_ERROR);
}
