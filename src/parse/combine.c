/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:42:11 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/15 10:52:11 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* In this programm, we combine the different tokens if they need to be combined
 (for example ec"ho") . We check the Start and end values of the subsequent 
 tokens.  We create a new token structure (combtok), which contained the tokens 
 that  have been concatenated, and we free the rest of the tokens.			  */

int			combine(t_shell *shell);
static int	set_index_combine(t_state *state);
static int	combine_tokens_iter(t_state *state, int new_count);
static int	val_comb(t_token **old_tok, t_token **comb_tok, int *new_n, int *i);
static void	free_combtok(t_token **comb_tok, int new_index);

int	combine(t_shell *sh)
{
	int	comb_count;

	if (sh->last_exit_code != NO_ERROR)
		return (sh->last_exit_code);
	else if (!sh->state || !sh->state->tokens || sh->state->token_count < 2)
		sh->last_exit_code = NO_ERROR;
	comb_count = set_index_combine(sh->state);
	if (comb_count > 0 && sh->last_exit_code == NO_ERROR)
		sh->last_exit_code = combine_tokens_iter(sh->state, 
				sh->state->token_count - comb_count);
	return (sh->last_exit_code);
}

static int	set_index_combine(t_state *state)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (state->tokens[i])
	{
		if (state->tokens[i]->start == state->tokens[i - 1]->end
			&& ft_is_comb(state->tokens[i]) && ft_is_comb(state->tokens[i - 1]))
		{
			state->tokens[i]->comb_prev = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	combine_tokens_iter(t_state *state, int new_count)
{
	int		i;
	t_token	**comb_token;
	int		new_index;

	comb_token = malloc(sizeof(t_token *) * (new_count + 1));
	if (!comb_token)
		return (MEMORY_ALLOCATION_ERROR);
	new_index = 0;
	comb_token[0] = state->tokens[0];
	i = 1;
	while (i < state->token_count)
	{
		if (val_comb(state->tokens, comb_token, &new_index, &i) == 1)
		{
			free_combtok(comb_token, new_index);
			return (GENERAL_ERROR);
		}
		i++;
	}
	free(state->tokens);
	state->tokens = comb_token;
	state->tokens[new_count] = NULL;
	state->token_count = new_count;
	return (NO_ERROR);
}

static int	val_comb(t_token **old_tok, t_token **comb_tok, int *new_n, int *i)
{
	char	*new_value;

	if (old_tok[*i]->comb_prev == true)
	{
		new_value = ft_strjoin(comb_tok[*new_n]->value, old_tok[*i]->value);
		if (!new_value)
			return (GENERAL_ERROR);
		if (comb_tok[*new_n]->value)
			free(comb_tok[*new_n]->value);
		comb_tok[*new_n]->value = new_value;
		comb_tok[*new_n]->length = ft_strlen(new_value);
		comb_tok[*new_n]->end = old_tok[*i]->end;
		free(old_tok[*i]->value);
		free(old_tok[*i]);
	}
	else
	{
		(*new_n)++;
		comb_tok[*new_n] = old_tok[*i];
	}
	return (NO_ERROR);
}

static void	free_combtok(t_token **comb_tok, int new_index)
{
	int	j;

	j = 0;
	if (comb_tok && *comb_tok)
	{
		while (j <= new_index)
		{
			if (comb_tok[j])
			{
				free(comb_tok[j]->value);
				free(comb_tok[j]);
				comb_tok[j] = NULL;
			}
			j++;
		}
		free(comb_tok);
		comb_tok = NULL;
	}
}
