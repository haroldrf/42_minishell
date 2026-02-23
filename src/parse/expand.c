/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:48:06 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/15 10:54:05 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			expand(t_shell *shell);
static void	update_expandable_index( t_state *state);
static void	handle_heredoc(t_state *state, int *i);
static bool	ft_is_exp(t_tok_type type);

/* if "expandable flag = true" and $ -> expand_token */
int	expand(t_shell *shell)
{
	int		i;

	update_expandable_index(shell->state);
	i = 0;
	while (i < shell->state->token_count)
	{
		if (shell->state->tokens[i]->expandable 
			&& ft_strchr(shell->state->tokens[i]->value, '$'))
		{
			shell->state->tokens[i]->value 
				= expand_string(shell->state->tokens[i]->value, shell);
			if (shell->state->tokens[i]->value == NULL)
				return (shell->last_exit_code = MEMORY_ALLOCATION_ERROR);
			shell->state->tokens[i]->length 
				= ft_strlen(shell->state->tokens[i]->value);
			shell->state->tokens[i]->retoken = true; 
		}
		i++;
	}
	if (shell->last_exit_code == MEMORY_ALLOCATION_ERROR)
		return (shell->last_exit_code);
	else
		return (shell->last_exit_code = NO_ERROR);
}

static bool	ft_is_exp(t_tok_type type)
{
	if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_APPEND
		|| type == TOKEN_REDIR_OUT || type == TOKEN_SINGLE_Q)
		return (false);
	return (true);
}

/* EXPANDABLE FLAG : which tokens can be expanded  */
static void	update_expandable_index(t_state *state)
{
	int	i;

	if (!state || !state->tokens)
		return ;
	i = 0;
	while (i < state->token_count)
	{
		if (ft_is_exp(state->tokens[i]->type))
			state->tokens[i]->expandable = true;
		if (state->tokens[i]->type == TOKEN_HEREDOC)
		{
			handle_heredoc(state, &i);
			continue ;
		}
		i++;
	}
}

/* IF HEREDOC: the DLM should not be expanded  -> flag non exp */
static void	handle_heredoc(t_state *state, int *i)
{
	(*i)++;
	if (*i < state->token_count)
	{
		state->tokens[*i]->expandable = false;
		(*i)++;
		while (*i < state->token_count 
			&& state->tokens[*i]->start == state->tokens[*i - 1]->end 
			&& ft_is_exp(state->tokens[*i]->type))
		{
			state->tokens[*i]->expandable = false;
			(*i)++;
		}
	}
}
