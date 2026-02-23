/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retoken.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:45:46 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/15 11:03:20 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			retoken(t_shell *shell);
static int	n_retoken(t_state *state);
static int	split_token(t_state *state, int n);
static int	handle_new_tokens(t_state *state, t_token **new_tok, int *j, int i);
static int	create_retokens(t_retoken *tok_data, int k);

int	retoken(t_shell *shell)
{
	int		n;
	int		exit;

	if (shell->last_exit_code != NO_ERROR)
		return (shell->last_exit_code);
	n = n_retoken(shell->state);
	if (n == 0)
		return (shell->last_exit_code);
	exit = split_token(shell->state, n);
	if (exit != NO_ERROR)
		return (shell->last_exit_code = exit);
	return (shell->last_exit_code = NO_ERROR);
}

// state retoken is by default false - these lines could be deleted
static int	n_retoken(t_state *state)
{
	int	i;
	int	n;
	int	count;

	i = 0;
	n = 0;
	while (i < state->token_count)
	{
		if (state->tokens[i]->value && state->tokens[i]->type != TOKEN_DOUBLE_Q
			&& state->tokens[i]->retoken == true)
		{
			count = count_elts(state->tokens[i]->value);
			if (count > 1)
			{
				n += count - 1;
				state->tokens[i]->retoken = true;
			}
			else
				state->tokens[i]->retoken = false;
		}
		else
			state->tokens[i]->retoken = false;
		i++;
	}
	return (n);
}

static int	split_token(t_state *state, int n)
{
	t_token	**new_tokens;
	int		i;
	int		j;

	new_tokens = malloc(sizeof(t_token *) * (state->token_count + n + 1));
	if (!new_tokens)
		return (MEMORY_ALLOCATION_ERROR);
	i = 0;
	j = 0;
	while (state->tokens[i])
	{
		if (state->tokens[i]->retoken == false)
			new_tokens[j++] = state->tokens[i];
		else if (handle_new_tokens(state, new_tokens, &j, i) != NO_ERROR)
		{
			free(new_tokens);
			return (MEMORY_ALLOCATION_ERROR);
		}
		i++;
	}
	new_tokens[j] = NULL;
	free(state->tokens);
	state->tokens = new_tokens;
	state->token_count = j;
	return (NO_ERROR);
}

static int	handle_new_tokens(t_state *state, t_token **new_tok, int *j, int i)
{
	int			k;
	t_retoken	tok_data;

	tok_data.j = j;
	tok_data.new_tok = new_tok;
	tok_data.old_tok = state->tokens[i];
	tok_data.split = ft_split(state->tokens[i]->value, ' ');
	if (!tok_data.split)
		return (MEMORY_ALLOCATION_ERROR);
	k = 0;
	while (tok_data.split[k])
	{
		if (create_retokens(&tok_data, k) != NO_ERROR)
		{
			free_split(tok_data.split, k);
			return (MEMORY_ALLOCATION_ERROR);
		}
		k++;
	}
	free_split(tok_data.split, k);
	free(state->tokens[i]->value);
	free(state->tokens[i]);
	return (NO_ERROR);
}

static int	create_retokens(t_retoken *tok_data, int k)
{
	tok_data->new_tok[*tok_data->j] = malloc(sizeof(t_token));
	if (!tok_data->new_tok[*tok_data->j])
	{
		free_split(tok_data->split, k);
		return (MEMORY_ALLOCATION_ERROR);
	}
	if (assign_values(tok_data, k) != NO_ERROR)
	{
		free(tok_data->new_tok[*tok_data->j]);
		free_split(tok_data->split, k);
		return (MEMORY_ALLOCATION_ERROR);
	}
	(*tok_data->j)++;
	return (NO_ERROR);
}
