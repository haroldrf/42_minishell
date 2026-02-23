/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:49:06 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/15 11:00:32 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Helper functions for the creation of the command nodes					  */

int				put_arg_redir(t_state *state, t_xnode *node, int start, int *i);
static int		handle_args(t_xnode *node, t_token *token, int *arg_index);
static int		handle_redir(t_xnode *node, t_token *token, int *redir_index);
static t_redir	*put_value_redir(t_token *token);

int	put_arg_redir(t_state *state, t_xnode *node, int start, int *i)
{
	int	arg_index;
	int	redir_index;
	int	j;
	int	result;

	arg_index = 0;
	redir_index = 0;
	result = NO_ERROR;
	j = start;
	while (j < *i)
	{
		if (state->tokens[j]->type == TOKEN_WORD)
			result = handle_args(node, state->tokens[j], &arg_index);
		else if (state->tokens[j]->type >= FILE_REDIR_IN 
			&& state->tokens[j]->type <= HEREDOC_DLM)
			result = handle_redir(node, state->tokens[j], &redir_index);
		if (result == GENERAL_ERROR)
			return (GENERAL_ERROR);
		j++;
	}
	node->argv[arg_index] = NULL;
	node->redir[redir_index] = NULL;
	return (NO_ERROR);
}

static int	handle_args(t_xnode *node, t_token *token, int *arg_index)
{
	node->argv[*arg_index] = ft_strdup(token->value);
	if (!node->argv[*arg_index])
	{
		cleanup_node(node);
		return (GENERAL_ERROR);
	}
	(*arg_index)++;
	return (NO_ERROR);
}

static int	handle_redir(t_xnode *node, t_token *token, int *redir_index)
{
	node->redir[*redir_index] = put_value_redir(token); 
	if (!node->redir[*redir_index])
	{
		cleanup_node(node);
		return (MEMORY_ALLOCATION_ERROR);
	}
	(*redir_index)++;
	return (NO_ERROR);
}

t_redir	*put_value_redir(t_token *token)
{
	t_redir	*redir;

	redir = malloc((sizeof(t_redir)));
	if (!redir)
		return (NULL);
	redir->redir_type = token->type - 8;
	if (token->type == HEREDOC_DLM)
	{
		redir->file = NULL;
		redir->heredoc_dlm = ft_strdup(token->value); 
	}
	else
	{
		redir->heredoc_dlm = NULL;
		redir->file = ft_strdup(token->value);
	}
	if ((token->type == HEREDOC_DLM && !redir->heredoc_dlm)
		|| (token->type != HEREDOC_DLM && !redir->file))
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}
