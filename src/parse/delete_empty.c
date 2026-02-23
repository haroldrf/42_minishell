/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hruiz-fr <hruiz-fr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:16:59 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/16 11:50:14 by hruiz-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			delete_empty(t_shell *shell);
static int	empty_token_count(t_state *state);
static void	assign_tokens(t_state *state, t_token **new_tokens, int n);

int	delete_empty(t_shell *shell)
{
	int		n;
	int		new_token_count;
	t_token	**new_tokens;

	if (shell->last_exit_code != NO_ERROR)
		return (shell->last_exit_code);
	n = empty_token_count(shell->state);
	if (n == shell->state->token_count)
		return (shell->last_exit_code = NO_TOKEN);
	if (n == 0)
		return (NO_ERROR);
	new_token_count = shell->state->token_count - n;
	new_tokens = malloc(sizeof(t_token *) * (new_token_count + 1));
	if (!new_tokens)
		return (shell->last_exit_code = MEMORY_ALLOCATION_ERROR);
	assign_tokens(shell->state, new_tokens, new_token_count);
	free(shell->state->tokens);
	new_tokens[new_token_count] = NULL;
	shell->state->tokens = new_tokens;
	shell->state->token_count = new_token_count;
	return (shell->last_exit_code = NO_ERROR);
}

static int	empty_token_count(t_state *sta)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < sta->token_count)
	{
		if (sta->tokens[i]->value && ft_strcmp(sta->tokens[i]->value, "") == 0
			&& !(sta->tokens[i]->type == TOKEN_DOUBLE_Q 
				|| sta->tokens[i]->type == TOKEN_SINGLE_Q))
			n++;
		i++;
	}
	return (n);
}

static void	assign_tokens(t_state *sta, t_token **new_tokens, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (sta->tokens[i] && j < n)
	{
		if ((sta->tokens[i]->value && ft_strcmp(sta->tokens[i]->value, "") != 0)
			|| sta->tokens[i]->type == 8 || sta->tokens[i]->type == 7)
		{
			new_tokens[j++] = sta->tokens[i];
			sta->tokens[i] = NULL;
		}
		else
		{
			free(sta->tokens[i]->value);
			free(sta->tokens[i]);
		}
		i++;
	}
	while (sta->tokens[i])
	{
		free(sta->tokens[i]->value);
		free(sta->tokens[i++]);
	}
}
