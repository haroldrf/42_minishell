/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:58 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/15 10:53:58 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_helpr	identify_operator(char *current);
t_token	*putval_q(char *start, char *end, t_state *state, t_tok_type t_type);
t_token	*putval_nq(char *start, char *end, t_state *state, t_tok_type t_type);
int		increase_tok_capacity(t_shell *shell, int *max_tok);

t_helpr	identify_operator(char *current)
{
	if (current[0] == '<' && current[1] == '<')
		return ((t_helpr){TOKEN_HEREDOC, 2});
	else if (current[0] == '>' && current[1] == '>')
		return ((t_helpr){TOKEN_APPEND, 2});
	else if (current[0] == '|')
		return ((t_helpr){TOKEN_PIPE, 1});
	else if (current[0] == '<')
		return ((t_helpr){TOKEN_REDIR_IN, 1});
	else if (current[0] == '>')
		return ((t_helpr){TOKEN_REDIR_OUT, 1});
	return ((t_helpr){TOKEN_INVALID, 0});
}

t_token	*putval_nq(char *start, char *end, t_state *state, t_tok_type t_type)
{
	t_token	*new_token;
	int		malloc_size;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = t_type;
	new_token->expandable = false;
	new_token->retoken = false;
	new_token->comb_prev = 0;
	new_token->start = start - state->input_string;
	new_token->end = end - state->input_string;
	malloc_size = end - start;
	new_token->value = malloc(sizeof(char) * (malloc_size + 1));
	if (!new_token->value)
	{
		free (new_token);
		return (NULL);
	}
	ft_strlcpy(new_token->value, start, malloc_size + 1);
	new_token->length = (int)ft_strlen(new_token->value);
	return (new_token);
}

t_token	*putval_q(char *start, char *end, t_state *state, t_tok_type t_type)
{
	t_token	*new_token;
	int		malloc_size;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = t_type;
	new_token->expandable = false;
	new_token->retoken = false;
	new_token->comb_prev = 0;
	new_token->start = start - state->input_string;
	new_token->end = end - state->input_string;
	malloc_size = end - start - 2;
	new_token->value = malloc(sizeof(char) * (malloc_size + 1));
	if (!new_token->value)
	{
		free (new_token);
		return (NULL);
	}
	ft_strlcpy(new_token->value, start + 1, malloc_size + 1);
	new_token->length = (int)ft_strlen(new_token->value);
	return (new_token);
}

int	increase_tok_capacity(t_shell *shell, int *max_tok)
{
	t_token	**new_tokens;
	int		i;
	int		new_max;

	new_max = *max_tok * 2;
	new_tokens = malloc(sizeof(t_token *) * new_max);
	if (!new_tokens)
		return (MEMORY_ALLOCATION_ERROR);
	i = 0;
	while (i < shell->state->token_count)
	{
		new_tokens[i] = shell->state->tokens[i];
		i++;
	}
	free(shell->state->tokens);
	shell->state->tokens = new_tokens;
	*max_tok = new_max;
	return (NO_ERROR);
}
