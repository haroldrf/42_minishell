/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:44:25 by htharrau          #+#    #+#             */
/*   Updated: 2024/10/12 13:14:07 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int				command(t_shell *shell);
static t_xnode	*create_node(t_state *state, int *i);
static void		count_arg_redir(t_token *token, int *n_arg, int *n_redir);
static t_xnode	*allocate_node(int n_arg, int n_redir);
static void		init_node(t_xnode *node, int n_arg, int n_redir);

int	command(t_shell *shell)
{
	int		i;
	t_xnode	*current_node;
	t_xnode	*new_node;

	if (shell->last_exit_code != NO_ERROR)
		return (shell->last_exit_code);
	current_node = NULL;
	shell->cmd_tree = NULL;
	i = 0;
	while (i < shell->state->token_count)
	{
		new_node = create_node(shell->state, &i);
		if (!new_node)
		{
			cleanup_cmd_tree(&shell->cmd_tree);
			return (shell->last_exit_code = MEMORY_ALLOCATION_ERROR);
		}
		new_node->prev = current_node;
		if (!shell->cmd_tree)
			shell->cmd_tree = new_node;
		else
			current_node->next = new_node;
		current_node = new_node;
	}
	return (NO_ERROR);
}

static t_xnode	*create_node(t_state *state, int *i)
{
	int		n_arg;
	int		n_redir;
	int		start;
	t_xnode	*node;

	start = *i;
	n_arg = 0;
	n_redir = 0;
	while (*i < state->token_count && state->tokens[*i]->type != TOKEN_PIPE)
		count_arg_redir(state->tokens[(*i)++], &n_arg, &n_redir);
	if (*i < state->token_count && state->tokens[*i]->type == TOKEN_PIPE)
		(*i)++;
	node = allocate_node(n_arg, n_redir);
	if (!node)
		return (NULL);
	if (put_arg_redir(state, node, start, i) != NO_ERROR)
	{
		cleanup_node(node);
		return (NULL);
	}
	return (node);
}

/* count words + redir to allocate */
static void	count_arg_redir(t_token *token, int *n_arg, int *n_redir)
{
	if (token->type == TOKEN_WORD)
		(*n_arg)++;
	if (token->type == FILE_APPEND || token->type == FILE_REDIR_IN 
		|| token->type == FILE_REDIR_OUT || token->type == HEREDOC_DLM)
		(*n_redir)++;
}

static t_xnode	*allocate_node(int n_arg, int n_redir)
{
	t_xnode	*node;

	node = malloc(sizeof(t_xnode));
	if (!node)
		return (NULL);
	node->argv = malloc(sizeof (char *) * (n_arg + 1));
	if (!node->argv)
	{
		free(node);
		return (NULL);
	}
	node->redir = malloc(sizeof(t_redir *) * (n_redir + 1));
	if (!node->redir)
	{
		free(node->argv);
		free(node);
		return (NULL);
	}
	init_node(node, n_arg, n_redir);
	return (node);
}

static void	init_node(t_xnode *node, int n_arg, int n_redir)
{
	int	i;

	i = 0;
	while (i <= n_arg)
		node->argv[i++] = NULL;
	i = 0;
	while (i <= n_redir)
		node->redir[i++] = NULL;
	node->prev = NULL;
	node->next = NULL;
}
