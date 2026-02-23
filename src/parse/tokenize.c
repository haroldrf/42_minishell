/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:09:12 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/16 10:52:02 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			tokenize(t_shell *shell, int max_tok);
static int	tokenize_loop(char **current, t_shell *shell, int max_tok);
static int	handle_quote(t_state *state, char **current);
static int	handle_ops(t_state *state, char **current);
static int	handle_word(t_state *state, char **current);

int	tokenize(t_shell *shell, int max_tok)
{
	char	*current;
	int		exit;

	exit = 0;
	if (shell->last_exit_code == MEMORY_ALLOCATION_ERROR)
		return (MEMORY_ALLOCATION_ERROR);
	current = shell->state->input_string;
	while (*current && exit == NO_ERROR)
		exit = tokenize_loop(&current, shell, max_tok);
	if (exit != NO_ERROR)
		shell->last_exit_code = exit;
	shell->state->tokens[shell->state->token_count] = NULL;
	return (exit);
}

static int	tokenize_loop(char **current, t_shell *shell, int max_tok)
{
	int	exit;

	while (**current != '\0')
	{
		if (shell->state->token_count == max_tok - 1)
		{
			exit = increase_tok_capacity(shell, &max_tok);
			if (exit != NO_ERROR)
				return (shell->last_exit_code = exit);
		}
		if (ft_isspace(**current))
		{
			(*current)++;
			continue ;
		}
		else if (ft_isquotes(**current))
			exit = handle_quote(shell->state, current);
		else if (ft_isops(**current))
			exit = handle_ops(shell->state, current);
		else 
			exit = handle_word(shell->state, current);
		if (exit != NO_ERROR)
			return (exit);
	}
	return (NO_ERROR);
}

// *current ++ : pass the quotes (at the beginning and at the end)
static int	handle_quote(t_state *state, char **current)
{
	char	*start;
	t_token	*new_token;

	start = *current;
	(*current)++;
	while (**current && **current != *start)
		(*current)++;
	if (**current == '\0')
	{
		ft_printf("Syntax error: unclosed quotes.\n");
		return (SHELL_BUILTIN_ERROR);
	}
	if (*start == '\'')
		new_token = putval_q(start, *current + 1, state, TOKEN_SINGLE_Q);
	else
		new_token = putval_q(start, *current + 1, state, TOKEN_DOUBLE_Q);
	if (!new_token)
		return (MEMORY_ALLOCATION_ERROR);
	(*current)++;
	state->tokens[state->token_count] = new_token;
	state->token_count++;
	return (NO_ERROR);
}

static int	handle_ops(t_state *state, char **current)
{
	char	*start;
	t_token	*new_token;
	t_helpr	helper; 

	start = *current;
	helper = identify_operator(*current);
	if (helper.type == TOKEN_INVALID)
		return (SHELL_BUILTIN_ERROR);
	*current += helper.step;
	new_token = putval_nq(start, *current, state, helper.type);
	if (!new_token)
		return (MEMORY_ALLOCATION_ERROR);
	state->tokens[state->token_count] = new_token;
	state->token_count++;
	return (NO_ERROR);
}

static int	handle_word(t_state *state, char **current)
{
	char	*start;
	t_token	*new_token;

	start = *current;
	while (**current && !ft_isspace(**current) 
		&& !ft_isops(**current) && !ft_isquotes(**current))
		(*current)++;
	if (*current == start)
		return (NO_ERROR);
	new_token = putval_nq(start, *current, state, TOKEN_WORD);
	if (!new_token)
		return (MEMORY_ALLOCATION_ERROR);
	state->tokens[state->token_count] = new_token;
	state->token_count++;
	return (NO_ERROR);
}
